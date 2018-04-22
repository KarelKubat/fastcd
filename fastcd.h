#include <ctype.h>
#include <dirent.h>
#include <iostream>
#include <mutex>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include <sys/types.h>

extern void choose();
extern std::string curdir();
extern char kbdchar();
extern void usage();
extern void solve(std::string const &initials);

// Sources that include this will only have references to EXTERN globals
// and will not instantiate them.
#ifndef EXTERN
#define EXTERN extern
#endif

EXTERN std::string keyselectors;
EXTERN std::vector<std::string> solutions;
