#include "fastcd.h"

static void sendsolution(std::string const &s) {
  solutionsmutex.lock();
  solutionsqueue.push(s);
  solutionsmutex.unlock();
}

static void solvehere(std::string const &initials) {
  // Initials exhausted? Enter in the queue of possibilities.
  if (initials.length() == 0) {
    sendsolution(curdir());
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

  // Send end-of-solutions marker
  sendsolution("");
}
