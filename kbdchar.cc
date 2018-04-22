#include "fastcd.h"

char kbdchar() {
  struct termios tattr, saved;
  char ch;

  tcgetattr(fileno (stdin), &saved);
  tcgetattr(fileno (stdin), &tattr);   
  tattr.c_lflag &= ~(ICANON | ECHO);
  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr(0, TCSAFLUSH, &tattr);
  read (fileno (stdin), &ch, 1);
  tcsetattr(fileno (stdin), TCSANOW, &saved);

  return ch;
}
  
