#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height): width(width), height(height)
{

  display = XOpenDisplay(NULL);
  if (display == NULL)
  {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  screen = DefaultScreen(display);
  window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10,
                                width, height, 1, BlackPixel(display, screen),
                                WhitePixel(display, screen));
  XSelectInput(display, window, ExposureMask | KeyPressMask);
  XMapRaised(display, window);

  Pixmap pix = XCreatePixmap(display, window, width, height,
                              DefaultDepth(display, DefaultScreen(display)));
  gc = XCreateGC(display, pix, 0, (XGCValues *) 0);

  XFlush(display);
  XFlush(display);

  // Set up colours.
  XColor xcolour;
  Colormap cmap;
  char color_vals[10][10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

  cmap = DefaultColormap(display, DefaultScreen(display));
  for (int i = 0; i < 10; ++i)
  {
    if (!XParseColor(display, cmap, color_vals[i], &xcolour))
    {
      cerr << "Bad colour: " << color_vals[i] << endl;
    }
    if (!XAllocColor(display, cmap, &xcolour))
    {
      cerr << "Bad colour: " << color_vals[i] << endl;
    }
    colours[i] = xcolour.pixel;
 }

  XSetForeground(display, gc, colours[Black]);

  // Make window non-resizeable.
  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(display, window, &hints);

  XSynchronize(display,True);

  usleep(1000);
}

Xwindow::~Xwindow()
{
  XFreeGC(display, gc);
  XCloseDisplay(display);
}

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour)
{
  XSetForeground(display, gc, colours[colour]);
  XFillRectangle(display, window, gc, x, y, width, height);
  XSetForeground(display, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg, int colour)
{
  XSetForeground(display, gc, colours[colour]);
  Font f = XLoadFont(display, "6x13");
  XTextItem ti;
  ti.chars = const_cast<char *>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
  ti.font = f;
  XDrawText(display, window, gc, x, y, &ti, 1);
  XSetForeground(display, gc, colours[Black]);
  XFlush(display);
}

void Xwindow::drawBigString(int x, int y, string msg, int colour, int scale)
{
  XSetForeground(display, gc, colours[colour]);

  ostringstream name;
  name << "-*-helvetica-bold-r-*-*-*-240-" << width/scale << "-" << height/scale << "-*-*-*-*";

  XFontStruct *f = XLoadQueryFont(display, name.str().c_str());
  XTextItem ti;
  ti.chars = const_cast<char *>(msg.c_str());
  ti.nchars = msg.length();
  ti.delta = 0;
  ti.font = f->fid;
  XDrawText(display, window, gc, x, y, &ti, 1);
  XSetForeground(display, gc, colours[Black]);
  XFlush(display);
}


