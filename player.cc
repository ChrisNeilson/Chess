#include "player.h"
#include "human.h"
#include "gameManager.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"
#include "ai1.h"
#include "ai2.h"
#include "ai3.h"
#include "ai4.h"

using namespace std;

Player::UPtr Player::whitePlayer_;
Player::UPtr Player::blackPlayer_;

Player::Player(char colour): colour_(colour), gm_(GameManager::getInstance()),
  pieces_(colour == 'w' ? gm_.getWhitePieces() : gm_.getBlackPieces()) {}

bool Player::pawnAtEnd(Piece::SPtr p, S8 row, S8 col)
{
  return (((row == 0 && colour_ == 'w') || (row == 7 && colour_ == 'b'))
            && p->getType() == Piece::Type::Pawn);
}

Player::~Player() {}

Player::UPtr & Player::getBlack()
{
  return blackPlayer_;
}

Player::UPtr & Player::getWhite()
{
  return whitePlayer_;
}

bool Player::setBlack(U8 playerType)
{
  switch(playerType)
  {
    case 0:
      blackPlayer_ = Player::UPtr(new Human('b'));
      break;
    case 1:
      blackPlayer_ = Player::UPtr(new AIOne('b'));
      break;
    case 2:
      blackPlayer_ = Player::UPtr(new AITwo('b'));
      break;
    case 3:
      blackPlayer_ = Player::UPtr(new AIThree('b'));
      break;
    case 4:
      blackPlayer_ = Player::UPtr(new AIFour('b'));
      break;
    default:
      cerr << "Invalid player type" << endl;
      return false;
  }
  return true;
}

bool Player::setWhite(U8 playerType)
{
  switch(playerType)
  {
    case 0:
      whitePlayer_ = Player::UPtr(new Human('w'));
      break;
    case 1:
      whitePlayer_ = Player::UPtr(new AIOne('w'));
      break;
    case 2:
      whitePlayer_ = Player::UPtr(new AITwo('w'));
      break;
    case 3:
      whitePlayer_ = Player::UPtr(new AIThree('w'));
      break;
    case 4:
      whitePlayer_ = Player::UPtr(new AIFour('w'));
      break;
    default:
      cerr << "Invalid player type" << endl;
      return false;
  }
  return true;
}

char Player::getColour()
{
  return colour_;
}

void Player::executeMove(S8 srcRow, S8 srcCol, S8 destRow, S8 destCol)
{
  Piece::SPtr p = gm_.getPiece(srcRow, srcCol);

  gm_.destroyPiece(destRow, destCol);
  gm_.movePiece(srcRow, srcCol, destRow, destCol);

  // set fields if necessary
  if (p->getType() == Piece::Type::King)
  {
    King::SPtr king = static_pointer_cast<King>(p);
    king->setHasMoved();
  }
  if (p->getType() == Piece::Type::Rook)
  {
    Rook::SPtr rook = static_pointer_cast<Rook>(p);
    rook->setHasMoved();
  }
  if (p->getType() == Piece::Type::Pawn && abs(destRow - srcRow) == 2)
  {
    Pawn::SPtr pawn = static_pointer_cast<Pawn>(p);
    pawn->setEnPassantAvail(true);
  }
}

void Player::clearEnPassant()
{
  for (auto i = pieces_.begin(); i != pieces_.end(); i++)
  {
    Piece::SPtr piece = *i;
    shared_ptr<Pawn> pawn = dynamic_pointer_cast<Pawn>(piece);
    if (pawn)
    {
      pawn->setEnPassantAvail(false);
    }
  }
}
