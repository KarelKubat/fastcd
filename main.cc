#include "fastcd.h"

int main(int argc, char **argv) {

  // Check args
  if (argc != 2)
    usage();

  std::thread solver(solve, argv[1]);
  solver.join();

  // All done
  return 0;
}
