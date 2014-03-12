#include "knight.h"

#include <cstdlib>

Knight::Knight(char colour) : Piece(colour) {}

Piece::Type Knight::getType()
{
  return Type::Knight;
}

U8 Knight::getValue()
{
  return 4;
}

bool Knight::isValidMove(S8 row, S8 col)
{
  return ((abs(row - row_) == 1 && abs(col - col_) == 2) ||
        (abs(row - row_) == 2 && abs(col - col_) == 1));
}
