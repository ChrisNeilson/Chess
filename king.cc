#include "gameManager.h"
#include "king.h"
#include "rook.h"

#include <cstdlib>
#include <memory>

using namespace std;

bool King::isValidCastle(S8 row, S8 col)
{
  S8 srcCol = col_;
  S8 srcRow = row_;

  if (hasMoved_)
  {
    return false;
  }

  GameManager &gm = GameManager::getInstance();

  // castle to right
  if (col > srcCol)
  {
    Piece::SPtr piece = gm.getPiece(row, 7);
    if (!piece)
    {
      return false;
    }

   Rook::SPtr rook = dynamic_pointer_cast<Rook>(piece);
    if ((!rook || rook->getHasMoved()) || gm.isCheck(colour_))
    {
      return false;
    }

    for (S8 i = srcCol + 1; i < 7; ++i)
    {
      if (gm.getPiece(row, i))
      {
        return false;
      }
      gm.movePiece(srcRow, srcCol, srcRow, i);
      if (gm.isCheck(colour_))
      {
        gm.movePiece(srcRow, i, srcRow, srcCol);
        return false;
      }
      gm.movePiece(srcRow, i, srcRow, srcCol);
    }
  }
  // castle to left
  else if (col < srcCol)
  {
    Piece::SPtr piece = gm.getPiece(row, 0);
    if (!piece)
    {
      return false;
    }

   Rook::SPtr rook = dynamic_pointer_cast<Rook>(piece);
    if ((!rook || rook->getHasMoved()) || gm.isCheck(colour_))
    {
      return false;
    }
    for (S8 i = srcCol - 1; i > 0; --i)
    {
      if (gm.getPiece(row, i))
      {
        return false;
      }
      gm.movePiece(srcRow, srcCol, srcRow, i);
      if (gm.isCheck(colour_))
      {
        gm.movePiece(srcRow, i, srcRow, srcCol);
        return false;
      }
      gm.movePiece(srcRow, i, srcRow, srcCol);
    }
  }
  return true;
}

King::King(char colour) : Piece(colour), hasMoved_(false) {}

Piece::Type King::getType()
{
  return Type::King;
}

U8 King::getValue()
{
  return 0;
}

bool King::isValidMove(S8 row, S8 col) {
  if (abs(row - row_) > 1 || abs(col - col_) > 2)
  {
    return false;
  }
  if (abs(col - col_) == 2)
  {
    return isValidCastle(row, col);
  }
  return true;
}

bool King::getHasMoved()
{
  return hasMoved_;
}

void King::setHasMoved()
{
  hasMoved_ = true;
}


