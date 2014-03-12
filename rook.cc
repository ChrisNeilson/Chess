#include "rook.h"

Rook::Rook(char colour, bool hasMoved) : Piece(colour), hasMoved_(hasMoved) {}

Piece::Type Rook::getType()
{
  return Type::Rook;
}

U8 Rook::getValue()
{
  return 6;
}

bool Rook::isValidMove(S8 row, S8 col)
{
  return (row == row_ || col == col_);
}

bool Rook::getHasMoved()
{
  return hasMoved_;
}

void Rook::setHasMoved()
{
  hasMoved_ = true;
}

