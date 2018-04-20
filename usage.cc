#include "fastcd.h"
#include "usage.h"

void usage() {
  std::cerr << "This is fastcd V" << VER << '\n';
  std::cerr << USAGETXT;
  exit(1);
}
