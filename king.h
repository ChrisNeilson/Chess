#ifndef __KING_H__
#define __KING_H__

#include "piece.h"

class King : public Piece
{
 private:
  bool hasMoved_;
  bool isValidCastle(S8 row, S8 col);

 public:
  typedef std::shared_ptr<King> SPtr;

  King(char colour);

  Piece::Type getType();
  U8 getValue();
  bool isValidMove(S8 row, S8 col);

  bool getHasMoved();
  void setHasMoved();
};

#endif
