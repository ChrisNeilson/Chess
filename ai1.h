#ifndef __AIONE_H__
#define __AIONE_H__

#include "ai.h"

class AIOne : public AI
{
 public:
  AIOne(char colour);
  U8 getType();
  void makeMove();
};

#endif
