#include "fastcd.h"

void displaysolution(size_t i) {
  if (i < 0 || i >= solutions.size())
    return;

  // Gather string to display, send to std::cerr in one go. First entry
  // may also be selected using the ENTER key. Make sure nice ANSI coloring
  // and resetting is applied, if -c/-d are used.
  std::ostringstream os;

  // selector
  if (optioncolor != "")
    os << optioncolor;
  if (i == 0)
    os << "default ";
  else
    os << "      " << keyselectors[i] << ' ';
  if (optioncolor != "")
    os << resetcolor;

  // directory
  if (directorycolor != "")
    os << directorycolor;
  if (!strncmp(solutions[i].c_str(), homedir.c_str(), homedir.size()))
    os << '~' << solutions[i].substr(homedir.size());
  else
    os << solutions[i];
  if (directorycolor != "")
    os << resetcolor;

  // done: output this option
  os << '\n';
  std::cerr << os.str();
}
