#include "fastcd.h"

static void solvehere(std::string const &initials) {
  std::string curd = curdir();
  static std::map<ino_t, bool> visited;

  if (initials.length() == 0) {
    // Initials exhausted? Enter in the queue of possibilities.
    if (solutions.size() >= keyselectors.length()) {
      // More solutions than keyselectors (keys to hit) are not allowed.
      std::cerr << "fastcd: too many solutions, refine search and retry\n";
      exit(1);
    }

    // Display solution and enter as a solution.
    solutions.push_back(curd);
    // Gather string to display, send to std::cerr in one go. First entry
    // may also be selected using the ENTER key. Make sure nice ANSI coloring
    // and resetting is applied, if -c/-d are used.
    std::ostringstream os;

    // selector
    if (optioncolor != "")
      os << optioncolor;
    os << keyselectors[solutions.size() - 1];
    if (solutions.size() == 1)
      os << ",ENTER ";
    else
      os << "       ";
    if (optioncolor != "")
      os << resetcolor;

    // directory
    if (directorycolor != "")
      os << directorycolor;
    if (!strncmp(curd.c_str(), homedir.c_str(), homedir.size()))
      os << '~' << curd.substr(homedir.size());
    else
      os << curd;
    if (directorycolor != "")
      os << resetcolor;

    // done: output this option
    os << '\n';
    std::cerr << os.str();
    return;
  }

  // Stop recursing if we've been here before or we can't stat the dir.
  ino_t in = statdir(curd);
  if (in == (ino_t)-1 || visited.count(in) > 0)
    return;
  visited[in] = true;

  // Solve for next character in the initials and recurse.
  std::vector<std::string> entries = scandir(initials[0]);
  for (std::string &entry: scandir(initials[0]))
    if (!chdir(entry.c_str())) {
      solvehere(initials.substr(1));
      chdir("..");
    }
}

static void solveby(std::string const &startdir, std::string const &initials) {
  // Get current working directory, or stop.
  std::string cwd = curdir();
  if (!cwd.length())
    return;

  // Go to start point, and solve from there.
  if (statdir(startdir) == (ino_t)-1)
    std::cerr << "fastcd: cannot access starting point " << startdir << '\n';
  else {
    if (!chdir(startdir.c_str())) {
      solvehere(initials);
      chdir(cwd.c_str());
    }
  }
}

void solve(std::string const &initials) {
  solveby(".", initials);
  solveby(homedir, initials);
  solveby("/", initials);

  // No solutions should just stop. One solution can cd into the found
  // match and stop.
  // Otherwise, let the chooser run its course (ie. wait for a keypress
  // and cd into the user-selected destination).
  switch (solutions.size()) {
    case 0:
      std::cerr << "fastcd: no solutions\n";
      exit(1);
    case 1:
      std::cout << solutions[0] << '\n';
      exit(0);
  }
}
