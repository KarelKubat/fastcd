#include "fastcd.h"

static bool initialized;

static void initialize() {
  if (initialized)
    return;
  initialized = true;
  cbreak();
  noecho();
}

char ncurseskeynowait() {
  initialize();
  nodelay(stdscr, TRUE);
  int ch = getch();
  nodelay(stdscr, FALSE);
  std::cout << "ncursesnowait: ch=" << int(ch) << '\n';
  return ch == ERR ? -1 : ch;
}

char ncurseskeywait() {
  initialize();
  int ch = getch();
  std::cout << "ncurseswait: ch=" << int(ch) << '\n';
  return ch;
}
