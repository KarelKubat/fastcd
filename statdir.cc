#include "fastcd.h"

ino_t statdir(std::string const &dirname) {
  struct stat st;

  if (stat(dirname.c_str(), &st)) {
    std::cerr << "fastcd: failed to stat " << dirname << ": "
	      << strerror(errno) << '\n';
    return (ino_t)-1;
  }
  if (!S_ISDIR(st.st_mode))
    return (ino_t)-1;

  return st.st_ino;
}
