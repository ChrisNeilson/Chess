#ifndef __AITWO_H__
#define __AITWO_H__

#include "ai.h"

class AITwo: public AI {
 public:
  AITwo(char colour);
  U8 getType();
  void makeMove();
};

#endif
