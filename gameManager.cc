#include "gameManager.h"
#include "piece.h"
#include "player.h"
#include <cstdlib>
#include <algorithm>

using namespace std;

GameManager GameManager::instance;

GameManager::GameManager() : grid(Grid(xw))
{
  for (S8 i = 0; i < 8; ++i)
  {
    for (S8 j = 0; j < 8; ++j)
    {
      possibleMoves_.push_back(make_tuple(i, j));
    }
  }
}

bool GameManager::hasValidMove(char colour)
{
  vector<Piece::SPtr> &pieces = colour == 'w' ? wPieces_ : bPieces_;
  for (auto pieceIter = pieces.begin(); pieceIter != pieces.end(); ++pieceIter)
  {
    Piece::SPtr piece = *pieceIter;
    for (auto move = possibleMoves_.begin(); move != possibleMoves_.end(); ++move)
    {
      S8 destRow = get<0>(*move);
      S8 destCol = get<1>(*move);
      if (isValidMove(piece, destRow, destCol))
      {
        return true;
      }
    }
  }
  return false;
}

bool GameManager::isValidMove(Piece::SPtr piece, S8 destRow, S8 destCol)
{
  bool valid = false;
  char colour = piece->getColour();
  S8 srcRow = piece->getRow();
  S8 srcCol = piece->getCol();

  if (srcRow == destRow && srcCol == destCol)
  {
    return false;
  }

  if (piece->isValidMove(destRow, destCol) && !arePiecesBetween(piece, destRow, destCol))
  {
    // Put the board in temporary end state and see if move results in self-check
    // If the destPiece is a king, this move would win us the game, it doesn't matter
    // if our king would then be in check
    Piece::SPtr destPiece = getPiece(destRow, destCol);
    if (destPiece)
    {
      if (destPiece->getColour() == colour)
      {
        return false;
      }
      if (destPiece->getType() == Piece::Type::King)
      {
        return true;
      }
      destroyPiece(destRow, destCol);
    }

    movePiece(srcRow, srcCol, destRow, destCol);
    valid = !isCheck(colour);

    // Put the board back
    movePiece(destRow, destCol, srcRow, srcCol);
    if (destPiece)
    {
      addPiece(destPiece, destRow, destCol);
    }
  }
  return valid;
}

GameManager &GameManager::getInstance()
{
  return instance;
}

Xwindow &GameManager::getWindow()
{
  return xw;
}

Piece::SPtr GameManager::getPiece(S8 row, S8 col)
{
  return grid.getPiece(row, col).lock();
}

vector<shared_ptr<Piece>> & GameManager::getBlackPieces()
{
  return bPieces_;
}

vector<shared_ptr<Piece>> & GameManager::getWhitePieces()
{
  return wPieces_;
}

vector<tuple<S8, S8>> GameManager::getPossibleMoves()
{
  return possibleMoves_;
}

// colour moves next
string GameManager::getStatus(char colour)
{
  if (isCheck(colour))
  {
    if (!hasValidMove(colour))
    {
      return "CheckMate";
    }
    else
    {
      return "Check";
    }
  }
  else if (!hasValidMove(colour))
  {
    return "StaleMate";
  }
  return "InPlay";
}

void GameManager::clearPieces()
{
  bPieces_.clear();
  wPieces_.clear();
  bKing_ = nullptr;
  wKing_ = nullptr;

  for (S8 i = 0; i < 8; ++i)
  {
    for (S8 j = 0; j < 8; ++j)
    {
      notifyDisplay(i, j);
    }
  }
}

void GameManager::notifyDisplay(S8 row, S8 col)
{
  grid.notifyDisplay(row, col);
}

void GameManager::addPiece(Piece::SPtr piece, S8 row, S8 col)
{
  destroyPiece(row, col);
  piece->setCoords(row, col);
  grid.addPiece(piece, row, col);
  char colour = piece->getColour();
  vector<Piece::SPtr> &pieces = colour == 'b' ? bPieces_ : wPieces_;
  pieces.push_back(piece);
  if (piece->getType() == Piece::Type::King)
  {
    colour == 'b' ? bKing_ = piece : wKing_ = piece;
  }
}

void GameManager::destroyPiece(S8 row, S8 col)
{
  Piece::SPtr piece = getPiece(row, col);
  grid.addPiece(nullptr, row, col);
  if (piece)
  {
    if (piece->getColour() == 'b')
    {
      for (auto iter = bPieces_.begin(); iter != bPieces_.end(); ++iter)
      {
        if (*iter == piece)
        {
          bPieces_.erase(iter);
          if (piece->getType() == Piece::Type::King)
          {
            bKing_ = nullptr;
          }
          return;
        }
      }
    }
    else
    {
      for (auto iter = wPieces_.begin(); iter != wPieces_.end(); ++iter)
      {
        if (*iter == piece)
        {
          wPieces_.erase(iter);
          if (piece->getType() == Piece::Type::King)
          {
            wKing_ = nullptr;
          }
          return;
        }
      }
    }
  }
}

void GameManager::movePiece(S8 srcRow, S8 srcCol, S8 destRow, S8 destCol)
{
  if (srcRow != destRow || srcCol != destCol)
  {
    grid.movePiece(srcRow, srcCol, destRow, destCol);
  }
}

void GameManager::setKing(Piece::SPtr king)
{
  king->getColour() == 'b' ? bKing_ = king : wKing_ = king;
 }

bool GameManager::arePiecesBetween(Piece::SPtr piece, S8 destRow, S8 destCol)
{
  S8 curRow = piece->getRow();
  S8 curCol = piece->getCol();

  if (curRow == destRow && curCol == destCol)
  {
    return false;
  }

  char colour = piece->getColour();
  Piece::SPtr destPiece = getPiece(destRow, destCol);
  if (destPiece && destPiece->getColour() == colour)
  {
    return true;
  }

  // same row
  if (curRow == destRow)
  {
    if (curCol > destCol)
    {
      swap(curCol, destCol);
    }
    while (++curCol < destCol)
    {
      Piece::SPtr curPiece = getPiece(curRow, curCol);
      if (curPiece)
      {
        return true;
      }
    }
  }
  else if (curCol == destCol)
  {
    if (curRow > destRow)
    {
      swap(curRow, destRow);
    }
    while (++curRow < destRow)
    {
      Piece::SPtr curPiece = getPiece(curRow, curCol);
      if (curPiece)
      {
        return true;
      }
    }
  }
  else if (abs(curRow - destRow) == abs(curCol - destCol))
  {
    if (curRow > destRow)
    {
      swap(curRow, destRow);
      swap(curCol, destCol);
    }
    while (++curRow < destRow)
    {
      if (curCol < destCol)
      {
        curCol++;
      }
      else
      {
        curCol--;
      }
      Piece::SPtr curPiece = getPiece(curRow, curCol);
      if (curPiece)
      {
        return true;
      }
    }
  }
  return false;
}

bool GameManager::isValidBoard()
{
  U8 blackKings = 0;
  U8 whiteKings = 0;
  for (auto it = bPieces_.begin(); it != bPieces_.end(); ++it)
  {
    Piece::SPtr piece = *it;
    if (piece->getType() == Piece::Type::King)
    {
      blackKings++;
    }
    else if (piece->getType() == Piece::Type::Pawn && piece->getRow() == grid.getSize())
    {
      return false;
    }
  }
  for (auto it = wPieces_.begin(); it != wPieces_.end(); ++it)
  {
    Piece::SPtr piece = *it;
    if (piece->getType() == Piece::Type::King)
    {
      whiteKings++;
    }
     else if (piece->getType() == Piece::Type::Pawn && piece->getRow() == 0)
    {
      return false;
    }
  }
  return (whiteKings == 1 && blackKings == 1);
}

bool GameManager::isCheck(char colour)
{
  vector<Piece::SPtr> &pieces = colour == 'b' ? wPieces_ : bPieces_;
  Piece::SPtr king = colour == 'b' ? bKing_ : wKing_;

  for (auto iter = pieces.begin(); iter != pieces.end(); ++iter)
  {
    if (isValidMove(*iter, king->getRow(), king->getCol()))
    {
      return true;
    }
  }
  return false;
}

bool GameManager::isUnderAttack(Piece::SPtr piece)
{
  vector<Piece::SPtr> &pieces = piece->getColour() == 'b' ? wPieces_ : bPieces_;
  for (auto iter = pieces.begin(); iter != pieces.end(); ++iter)
  {
    if (isValidMove(*iter, piece->getRow(), piece->getCol()))
    {
      return true;
    }
  }
  return false;
}




