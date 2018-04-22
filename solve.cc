#include "fastcd.h"

static void solvehere(std::string const &initials) {
  std::string curd = curdir();
  static std::map<std::string, bool> visited;
  
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
    // may also be selected using the ENTER key.
    std::ostringstream os;
    os << keyselectors[solutions.size() - 1];
    if (solutions.size() == 1)
      os << ",ENTER ";
    else
      os << "       ";
    os << curd << '\n';
    std::cerr << os.str();
    return;
  }

  // Stop recursing if we've been here before or we can't stat the dir.
  ino_t in = statdir(curd);
  if (in == (ino_t)-1 || visited.count(curd) > 0)
    return;
  visited[curd] = true;

  // Solve for next character in the initials and recurse.
  DIR *dirp = opendir(".");
  if (!dirp)
    return;

  struct dirent *direntp;
  while ( (direntp = readdir(dirp)) ) {
    bool match;
    if (ignorecase)
      match = tolower(direntp->d_name[0]) == tolower(initials[0]);
    else
      match = direntp->d_name[0] == initials[0];
    if (match && !chdir(direntp->d_name)) {
      // Possible match
      solvehere(initials.substr(1));
      chdir("..");
    }
  }
  closedir(dirp);
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
  solveby(getenv("HOME"), initials);
  solveby("/", initials);

  if (solutions.size() == 0) {
    std::cerr << "fastcd: no solutions\n";
    exit(1);
  }
}
