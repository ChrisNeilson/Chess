#ifndef __GRID_H__
#define __GRID_H__

#include "cell.h"
#include "types.h"
#include "window.h"

#include <array>
#include <memory>

class Piece;

class Grid
{
 private:
  static const S8 GRID_SIZE = 8;

  Xwindow &w;
  std::array<std::array<Cell, GRID_SIZE>, GRID_SIZE> theGrid;

  public:
  Grid(Xwindow &w);

  S8 getSize();
  std::weak_ptr<Piece> getPiece(S8 row, S8 col);
  void addPiece(std::shared_ptr<Piece> piece, S8 row, S8 col);
  void movePiece(S8 srcRow, S8 srcCol, S8 destRow, S8 destCol);
  void notifyDisplay(S8 row, S8 col);
};

#endif

