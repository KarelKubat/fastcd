#include "fastcd.h"

void choose() {
  while (true) {
    // Read key press
    char ch = kbdchar();

    // ENTER is interpreted as the first one in the row
    if (ch == '\r' || ch == '\n')
      ch = keyselectors[0];

    // If ch is outside of the key selectors or if it indexes a non-existing
    // solution, then redo.
    std::size_t index = keyselectors.find(ch);
    if (index == std::string::npos)
      continue;
    if (index >= solutions.size())
      continue;

    // Show solution on stdout for pickup by the shell and stop.
    std::cout << solutions[index] << '\n';
    exit(0);
  }
}
