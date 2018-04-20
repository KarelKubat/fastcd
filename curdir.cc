#include "fastcd.h"

std::string curdir() {
  char buf[FILENAME_MAX + 1];

  if (!getcwd(buf, FILENAME_MAX) || !*buf)
    return "";
  return buf;
}
