#include "gameManager.h"
#include "pawn.h"

#include <cstdlib>
#include <memory>

using namespace std;

bool Pawn::isValidEnPassant(S8 row, S8 col)
{
  Pawn::SPtr pawn = dynamic_pointer_cast<Pawn>(GameManager::getInstance().getPiece(row_, col));
  return (pawn && pawn->getColour() != colour_ && pawn->enPassantAvail_);
}

Pawn::Pawn(char colour): Piece(colour), enPassantAvail_(false) {}

Piece::Type Pawn::getType()
{
  return Type::Pawn;
}

U8 Pawn::getValue()
{
  return 1;
}

bool Pawn::isValidMove(S8 row, S8 col) {
  S8 dir = colour_ == 'b' ? 1 : -1; // multiplier for direction of movement

  S8 deltaX = col - col_;
  S8 deltaY = row - row_;
  Piece::SPtr destPiece = GameManager::getInstance().getPiece(row, col);

  // normal move
  if ((dir * deltaY == 1) && deltaX == 0 && !destPiece)
  {
    return true;
  }

  // capturing move (including en passant)
  if ((dir * deltaY == 1) && abs(deltaX) == 1)
  {
    return (destPiece || isValidEnPassant(row, col));
  }

  // 2-square move at start of game
  if (deltaX == 0 && dir * deltaY == 2 && !destPiece)
  {
    return ((colour_ == 'b' && row_ == 1) || (colour_ == 'w' && row_ == 6));
  }
  return false;
}

bool Pawn::getEnPassantAvail()
{
  return enPassantAvail_;
}

void Pawn::setEnPassantAvail(bool avail)
{
  enPassantAvail_ = avail;
}
