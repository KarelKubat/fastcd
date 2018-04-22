#include "fastcd.h"

void choose() {
  while (true) {
    std::size_t index = keyselectors.find(kbdchar());
    if (index == std::string::npos)
      continue;
    index--;
    if (index >= solutions.size())
      continue;

    std::cout << solutions[index] << '\n';
    exit(0);
  }
}
