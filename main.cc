// EXTERN marked globals will be instantiated in this object.
#define EXTERN

#include "fastcd.h"

static std::string colorcode(std::string opt) {
  // Known prefixes (modifiers to colors)
  static std::map<std::string, std::string> prefixes = {
    { "bright",    "1" },
    { "underline", "4" },
    { "inverse",   "7" }
  };
  // Known colors
  static std::map<std::string, std::string> colors = {
    { "black",   "30" },
    { "red",     "31" },
    { "green",   "32" },
    { "yellow",  "33" },
    { "blue",    "34" },
    { "magenta", "35" },
    { "cyan",    "36" },
    { "white",   "37" }
  };
  // Return escape sequence, magic-start + 0 for reset
  std::string ret = "\033[0";

  // Match prefixes, as many as there are
  bool prefix_found = true;
  while (prefix_found) {
    prefix_found = false;
    for (auto const &prefixentry: prefixes) {
      // prefixentry.first is the modifier, .second is the escape sequence
      if (opt.compare(0, prefixentry.first.length(), prefixentry.first) == 0) {
        prefix_found = true;
        ret += ';' + prefixentry.second;
        opt = opt.substr(prefixentry.first.length());
      }
    }
  }

  // Match one single color
  bool color_found = false;
  for (auto const &colorentry: colors) {
    // colorentry.first is the color, .second is the escape sequence
    if (opt == colorentry.first) {
      ret += ";" + colorentry.second;
      color_found = true;
    }
  }

  if (!color_found) {
    std::cerr << "fastcd: '" << opt << "' doesn't represent a color\n";
    exit(1);
  }

  // Add closing magic and bedone
  ret += 'm';
  return ret;
}

int main(int argc, char **argv) {
  // Initialization
  keyselectors =
      "0123456789"
      "abcdefghijklmnopqrstuvwxyz"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  ignorecase = false;
  homedir = getenv("HOME");
  // resetcolor is used when optioncolor and/or directorycolor are made active
  // using -k / -d
  resetcolor = "\033[0m";

  // Parse flags
  int opt;
  while ( (opt = getopt(argc, argv, "?hivk:d:")) != -1 )
    switch (opt) {
      case '?':
      case 'h':
        usage();
      case 'i':
        ignorecase = true;
        break;
      case 'k':
        optioncolor = colorcode(optarg);
        break;
      case 'd':
        directorycolor = colorcode(optarg);
        break;
      case 'v':
        std::cerr << VER << '\n';
        exit(0);
    }

  // Check args: one more argument (beyond flags) expected.
  if (argc - optind != 1)
    usage();

  // Make sure to reset the tty upon exiting.
  std::atexit(cleanup);

  // Start solver: it will display solutions, prefixed by characters from
  // the keyselectors.
  std::thread solver(solve, argv[optind]);

  // Start chooser: it will read a key, and if it indexes one of the solutions,
  // display that solution and quit.
  std::thread chooser(choose);

  // Chooser exits upon completion, joining the threads and returning from
  // main is not really necessary.
  solver.join();
  chooser.join();
  return 0;
}
