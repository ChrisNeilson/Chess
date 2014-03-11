#ifndef __AI_H__
#define __AI_H__

#include "player.h"

class AI : public Player
{
 protected:
  void makeMove(S8 srcRow, S8 srcCol, S8 destRow, S8 destCol);
  virtual void chooseNewPiece(std::shared_ptr<Piece> piece);

 public:
  AI(char colour);
  virtual U8 getType() = 0; // Returns AI level
  virtual void makeMove() = 0; // Makes a move
};

#endif
