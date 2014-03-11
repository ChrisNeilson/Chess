#ifndef __BISHOP_H__
#define __BISHOP_H__

#include "piece.h"

class Bishop : public Piece
{
 public:
  Bishop(char colour);

  Type getType();
  U8 getValue();
  bool isValidMove(S8 row, S8 col);
};

#endif
