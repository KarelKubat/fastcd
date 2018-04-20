// EXTERN marked globals will be instantiated in this object.
#define EXTERN

#include "fastcd.h"

int main(int argc, char **argv) {

  // Check args
  if (argc != 2)
    usage();

  std::thread solver(solve, argv[1]);
  std::thread ui(displayandchoose);

  solver.join();
  ui.join();

  // All done
  return 0;
}
