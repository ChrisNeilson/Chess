#ifndef __AITHREE_H__
#define __AITHREE_H__

#include "ai.h"

class AIThree: public AI {
 public:
  AIThree(char colour);
  U8 getType();
  void makeMove();
};

#endif
