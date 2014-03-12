#ifndef __AIFOUR_H__
#define __AIFOUR_H__

#include "ai.h"
#include "types.h"

class AIFour : public AI
{
 private:
  int calcScore(S8 srcRow, S8 srcCol, S8 destRow, S8 destCol);
  void populateMaxValueMoves(std::vector<std::tuple<std::tuple<S8, S8>, std::tuple<S8, S8>>> &moves);

 public:
  AIFour(char colour);
  U8 getType();
  void makeMove();
};

#endif
