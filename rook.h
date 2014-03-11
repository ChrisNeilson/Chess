#ifndef __ROOK_H__
#define __ROOK_H__

#include "piece.h"

class Rook : public Piece
{
 private:
  bool hasMoved_;

 public:
  typedef std::shared_ptr<Rook> SPtr;
  typedef std::weak_ptr<Rook> WPtr;

  Rook(char colour, bool hasMoved=false);

  Type getType();
  U8 getValue();
  bool isValidMove(S8 row, S8 col);

  bool getHasMoved();
  void setHasMoved();
};

#endif
