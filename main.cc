// EXTERN marked globals will be instantiated in this object.
#define EXTERN

#include "fastcd.h"

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
  while ( (opt = getopt(argc, argv, "?hivk:d:PC")) != -1 )
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
      case 'P':
        std::cout << "Available colorization prefixes:\n";
        for (auto const &prefix: all_prefixes())
          std::cout << "    " << prefix << '\n';
        exit(0);
      case 'C':
        std::cout << "Available colors:\n";
        for (auto const &color: all_colors())
          std::cout << "    " << color << '\n';
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
