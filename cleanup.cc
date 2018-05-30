#include "fastcd.h"

// Called atexit() just to make sure that the terminal is reset to a readable
// state.
void cleanup() {
  tcsetattr(fileno(stdin), TCSANOW, &saved_termios);
}
