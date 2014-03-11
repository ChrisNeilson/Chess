#ifndef __PIECE_H__
#define __PIECE_H__

#include "types.h"

#include <memory>

class Piece
{
 protected:
  char colour_;
  S8 row_;
  S8 col_;

 public:
  typedef std::shared_ptr<Piece> SPtr;
  typedef std::weak_ptr<Piece> WPtr;

  enum class Type { Bishop, King, Knight, Pawn, Queen, Rook };

  Piece(char colour);
  virtual ~Piece() {};

  char getColour();
  S8 getRow();
  S8 getCol();
  void setCoords(S8 row, S8 col);

  virtual Type getType() = 0;
  virtual U8 getValue() = 0;
  virtual bool isValidMove(S8 row, S8 col) = 0;
};

#endif
