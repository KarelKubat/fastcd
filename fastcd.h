#include <ctype.h>
#include <dirent.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include <sys/types.h>

extern std::string curdir();
extern void usage();
extern void solve(std::string const &initials);
