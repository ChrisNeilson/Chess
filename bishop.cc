#include "bishop.h"

#include <cstdlib>

Bishop::Bishop(char colour): Piece(colour) {}

Piece::Type Bishop::getType()
{
    return Type::Bishop;
}

U8 Bishop::getValue()
{
    return 4;
}

bool Bishop::isValidMove(S8 row, S8 col)
{
  return (abs(row - row_) == abs(col - col_));
}
