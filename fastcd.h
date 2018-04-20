#include <ctype.h>
#include <dirent.h>
#include <iostream>
#include <mutex>
#include <ncurses.h>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include <sys/types.h>

extern void choosefinal();
extern std::string curdir();
extern void displayandchoose();
extern char ncurseskeywait();
extern char ncurseskeynowait();
extern void ncursesinit();
extern void usage();
extern void solve(std::string const &initials);

// Sources that include this will only have references to EXTERN globals
// and will not instantiate them.
#ifndef EXTERN
#define EXTERN extern
#endif

EXTERN std::mutex solutionsmutex;
EXTERN std::queue<std::string> solutionsqueue;
