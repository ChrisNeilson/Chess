#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "piece.h"

class Queen : public Piece
{
 public:
  Queen(char colour);

  Type getType();
  U8 getValue();
  bool isValidMove(S8 row, S8 col);
};

#endif
