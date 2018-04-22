#include "fastcd.h"

std::vector<std::string> scandir(char initial) {
  std::vector<std::string> list;

  // Scan cwd, populate return value with directories under cwd that
  // start with the initial.
  DIR *dirp = opendir(".");
  if (!dirp) {
    std::cerr << "fastcd: failed to opendir " << curdir() << '\n';
    return list;
  }

  // Read cwd, add entries to the list
  struct dirent *direntp;
  while ( (direntp = readdir(dirp)) ) {
    bool match;
    if (ignorecase)
      match = tolower(direntp->d_name[0]) == tolower(initial);
    else
      match = direntp->d_name[0] == initial;
    if (match && statdir(direntp->d_name) != (ino_t)-1)
      list.push_back(direntp->d_name);
  }
  closedir(dirp);

  // Sort the list in alpha order and return.
  sort(list.begin(), list.end());
  return list;
}
