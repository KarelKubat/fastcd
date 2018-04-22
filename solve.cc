#include "fastcd.h"

static void solvehere(std::string const &initials) {
  if (initials.length() == 0) {
    // Initials exhausted? Enter in the queue of possibilities.
    if (solutions.size() >= keyselectors.length()) {
      // More solutions than keyselectors (keys to hit) are not allowed.      
      std::cerr << "Too many solutions, refine search and retry\n";
      exit(1);
    }

    // Display solution and enter as a solution.
    std::string curd = curdir();
    solutions.push_back(curd);
    std::cerr << keyselectors[solutions.size()] << ' ' << curd << '\n';
    return;
  }

  // Solve for next character in the initials and recurse.
  DIR *dirp = opendir(".");
  if (!dirp)
    return;

  struct dirent *direntp;
  while ( (direntp = readdir(dirp)) ) {
    if (tolower(direntp->d_name[0]) == tolower(initials[0]) &&
        !chdir(direntp->d_name)) {
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
  if (!chdir(startdir.c_str())) {
    solvehere(initials);
    chdir(cwd.c_str());
  }
}

void solve(std::string const &initials) {
  solveby(".", initials);
  solveby(getenv("HOME"), initials);
  solveby("/", initials);
}
