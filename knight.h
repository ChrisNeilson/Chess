#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "piece.h"

class Knight : public Piece
{
 public:
  Knight(char colour);

  Type getType();
  U8 getValue();
  bool isValidMove(S8 row, S8 col);
};

#endif
