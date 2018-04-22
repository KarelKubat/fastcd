#include "fastcd.h"

void cleanup() {
  tcsetattr(fileno (stdin), TCSANOW, &saved_termios);
}  
