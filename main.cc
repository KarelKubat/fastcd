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

  // Parse flags
  int opt;
  while ( (opt = getopt(argc, argv, "?hiv")) != -1 )
    switch (opt) {
    case '?':
    case 'h':
      usage();
    case 'i':
      ignorecase = true;
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
