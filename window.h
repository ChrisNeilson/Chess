#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <string>
#include "types.h"

class Xwindow
{
  Display *display;
  Window window;
  int screen;
  GC gc;
  U32 colours[10];
  int width, height;

 public:
  Xwindow(int width=500, int height=550);
  ~Xwindow();

  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown}; // Available colours.

  void fillRectangle(int x, int y, int width, int height, int colour=Black);
  void drawString(int x, int y, std::string msg, int colour=Black);
  void drawBigString(int x, int y, std::string msg, int colour=Black, int scale=5);
};

#endif
