#ifndef __CELL_H__
#define __CELL_H__

#include "types.h"

#include <memory>

class Piece;
class Xwindow;



class Cell
{
 private:
  char colour;
  Xwindow *window;
  S8 row, col;
  U32 width, height;
  std::weak_ptr<Piece> piece;

 public:
  static const int MAX_NEIGHBOURS = 8;

  Cell();
  std::weak_ptr<Piece> getPiece();
  void setCoords(S8 row, S8 col, Xwindow *w);
  void setPiece(std::shared_ptr<Piece> piece);
  void draw();
};

#endif

