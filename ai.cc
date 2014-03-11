#include "ai.h"
#include "gameManager.h"
#include "piece.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "knight.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void AI::makeMove(S8 srcRow, S8 srcCol, S8 destRow, S8 destCol)
{
  Piece::SPtr piece = gm_.getPiece(srcRow, srcCol);
  Player::executeMove(srcRow, srcCol, destRow, destCol);
  if (pawnAtEnd(piece, destRow, destCol))
  {
    chooseNewPiece(piece);
  }
  gm_.notifyDisplay(srcRow, srcCol);
  gm_.notifyDisplay(destRow, destCol);
}

void AI::chooseNewPiece(Piece::SPtr current)
{
  Piece::Type pieceTypes[4] = {
                                Piece::Type::Rook,
                                Piece::Type::Knight,
                                Piece::Type::Bishop,
                                Piece::Type::Queen
                                };
  Piece::Type pieceType = pieceTypes[rand() % 4];
  Piece::SPtr newPiece;
  switch(pieceType)
  {
    case Piece::Type::Rook:
      newPiece = Piece::SPtr(new Rook(colour_, true));
      break;
    case Piece::Type::Knight:
      newPiece = Piece::SPtr(new Knight(colour_));
      break;
    case Piece::Type::Bishop:
      newPiece = Piece::SPtr(new Bishop(colour_));
      break;
    case Piece::Type::Queen:
      newPiece = Piece::SPtr(new Queen(colour_));
      break;
  }
  S8 row = current->getRow();
  S8 col = current->getCol();
  gm_.destroyPiece(row, col);
  gm_.addPiece(newPiece, row, col);
}

AI::AI(char colour): Player(colour) {}
