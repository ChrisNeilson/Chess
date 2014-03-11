#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "player.h"

class Piece;

class Human: public Player
{
 public:
  Human(char colour);
  U8 getType();
  void getMove(S8 &srcRow, S8 &srcCol, S8 &destRow, S8 &destCol);
  void makeMove();
  void chooseNewPiece(std::shared_ptr<Piece> current);
};

#endif
