#ifndef __AIFOUR_H__
#define __AIFOUR_H__

#include "ai.h"

class AIFour : public AI
{
 private:
  int calcScore(S8 srcRow, S8 srcCol, S8 destRow, S8 destCol);

 public:
  AIFour(char colour);
  U8 getType();
  void makeMove();
};

#endif
