#include "queen.h"

#include <cstdlib>

Queen::Queen(char colour) : Piece(colour) {}

Piece::Type Queen::getType()
{
  return Type::Queen;
}

U8 Queen::getValue()
{
  return 8;
}

bool Queen::isValidMove(S8 row, S8 col)
{
  return (abs(row - row_) == abs(col - col_) || row == row_ || col == col_);
}
