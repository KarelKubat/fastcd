// EXTERN marked globals will be instantiated in this object.
#define EXTERN

#include "fastcd.h"

int main(int argc, char **argv) {
  // Check args
  if (argc != 2)
    usage();

  // Initialization
  keyselectors =
    "0123456789"
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";    

  std::thread solver(solve, argv[1]);
  std::thread chooser(choose);

  solver.join();
  chooser.join();

  // All done
  return 0;
}
