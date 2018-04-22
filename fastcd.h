#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <map>
#include <mutex>
#include <queue>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>

extern void choose();
extern void cleanup();
extern std::string curdir();
extern char kbdchar();
extern void usage();
extern void solve(std::string const &initials);
extern ino_t statdir(std::string const &dirname);

// Sources that include this will only have references to EXTERN globals
// and will not instantiate them.
#ifndef EXTERN
#define EXTERN extern
#endif

// Termio flags. Need to be global for cleanup.
EXTERN struct termios saved_termios;

// Flag: ignore case?
EXTERN bool ignorecase;

// String of keys users may press
EXTERN std::string keyselectors;

// Vector of solved directories
EXTERN std::vector<std::string> solutions;
