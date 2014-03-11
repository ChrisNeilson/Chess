#ifndef __PAWN_H__
#define __PAWN_H__

#include "piece.h"

class Pawn : public Piece
{
 private:
  bool enPassantAvail_;
  bool isValidEnPassant(S8 row, S8 col);

 public:
  typedef std::shared_ptr<Pawn> SPtr;
  typedef std::weak_ptr<Pawn> WPtr;

  Pawn(char colour);

  Type getType();
  U8 getValue();
  bool isValidMove(S8 row, S8 col);

  bool getEnPassantAvail();
  void setEnPassantAvail(bool avail);
};

#endif
