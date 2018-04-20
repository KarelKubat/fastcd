#include "fastcd.h"

// Given a size, return a selector that the user can hit for an entry.
// E.g.: 1,2,3 ... a,b,c ... A,B,C
static std::string keyselectors =
    "0123456789"
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static char size2selector(size_t n) {
  if (n < keyselectors.length())
    return keyselectors[n];
  std::cerr << "Too many solutions, refine your search.\n"
            << "(What kind of directory structure are you on?!\n";
  exit(1);
}

static size_t selector2index(char ch) {
  return keyselectors.find(ch);
}

static std::vector<std::string> solutions;
void displayandchoose() {
  while (true) {

    // Wait for something to arrive on the queue.
    solutionsmutex.lock();
    while (solutionsqueue.empty()) {
      solutionsmutex.unlock();
      solutionsmutex.lock();
    }

    std::string nextsolution = solutionsqueue.front();
    solutionsqueue.pop();
    solutionsmutex.unlock();

    // Empty string is sent as end-of-solutions marker.
    if (nextsolution == "")
      break;
    solutions.push_back(nextsolution);

    // Solutions are still being generated. If there's a keystroke
    // available, use it now.
    std::cout << size2selector(solutions.size()) << ' ' << nextsolution << '\n';

    // If there is a keystroke, read it and evaluate.
    char ch;
    if ( (ch = ncurseskeynowait()) != -1 ) {
      std::size_t index = selector2index(ch);
      if (index != std::string::npos)
        std::cout << solutions[index] << '\n';
    }
  }

  // Done gathering solutions.
  if (!solutions.size()) {
    std::cerr << "No solutions.\n";
    return;
  }

  char ch = ncurseskeywait();
  std::size_t index = selector2index(ch);
  if (index != std::string::npos)
    std::cout << solutions[index] << '\n';
}
