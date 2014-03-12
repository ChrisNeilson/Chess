#include "ai4.h"
#include "gameManager.h"
#include "piece.h"

#include <cstdlib>

using namespace std;

AIFour::AIFour(char colour): AI(colour) {}

U8 AIFour::getType()
{
  return 4;
}

int AIFour::calcScore(S8 srcRow, S8 srcCol, S8 destRow, S8 destCol)
{
  int score = 0;
  char colour = colour_ == 'b' ? 'w' : 'b'; // Opponent's colour
  Piece::SPtr piece = gm_.getPiece(srcRow, srcCol);

  // destPiece is not necessarily at (destRow, destCol) due to En Passant
  S8 destPieceRow = destRow;

  // Prefer to move piece out of danger
  if (gm_.isUnderAttack(piece))
  {
    score += piece->getValue();
  }

  Piece::SPtr destPiece = gm_.getPiece(destRow, destCol);
  // En Passant
  if (piece->getType() == Piece::Type::Pawn && abs(destCol - srcCol) == 1 && !destPiece)
  {
    destPieceRow = srcRow;
    destPiece = gm_.getPiece(destPieceRow, destCol);
  }

  // Temporarily put board in final state
  gm_.destroyPiece(destPieceRow, destCol);
  gm_.movePiece(srcRow, srcCol, destRow, destCol);

  if (destPiece)
  {
    score += (destPiece->getValue());
  }

  string status = gm_.getStatus(colour);
  if (status == "Check")
  {
    score += 1;
  }
  else if (status == "CheckMate")
  {
    score += 1000;
  }
  else if (status == "StaleMate")
  {
    score -= 10; // Stalemates are boring and this AI isn't that smart
  }

  // Prefer not to move piece into danger
  if (gm_.isUnderAttack(piece))
  {
    score -= (piece->getValue());
  }

  // put the board back
  gm_.movePiece(destRow, destCol, srcRow, srcCol);
  if (destPiece)
  {
    gm_.addPiece(destPiece, destPieceRow, destCol);
  }

  return score;
}

void AIFour::populateMaxValueMoves(vector<tuple<tuple<S8, S8>, tuple<S8, S8>>> &potentialMoves)
{
  vector<Piece::SPtr> untriedPieces(pieces_);
  srand(time(NULL));

  int maxScore = numeric_limits<int>::min();

  // Try every possible move for every piece
  for (auto pieceIter = untriedPieces.begin(); pieceIter != untriedPieces.end(); ++pieceIter)
  {
    Piece::SPtr piece = *pieceIter;
    S8 srcRow = piece->getRow();
    S8 srcCol = piece->getCol();

    vector<tuple<S8, S8>> untriedMoves(gm_.getPossibleMoves());

    for (vector<tuple<S8, S8>>::iterator moveIter = untriedMoves.begin();
         moveIter != untriedMoves.end(); ++moveIter)
    {
      S8 destRow = get<0>(*moveIter);
      S8 destCol = get<1>(*moveIter);

      // If move is valid, calculate score
      if (gm_.isValidMove(piece, destRow, destCol))
      {
        int score = calcScore(srcRow, srcCol, destRow, destCol);
        if (score > maxScore)
        {
          potentialMoves.clear();
          maxScore = score;
        }
        if (score >= maxScore)
        {
          tuple<S8, S8> srcCoords = make_tuple(srcRow, srcCol);
          tuple<S8, S8> destCoords = make_tuple(destRow, destCol);
          potentialMoves.push_back(make_tuple(srcCoords, destCoords));
        }
      }
    }
  }
}

void AIFour::makeMove()
{
  clearEnPassant();
  vector<tuple<tuple<S8, S8>, tuple<S8, S8>>> potentialMoves;
  populateMaxValueMoves(potentialMoves);


  // Choose a random move of maximum score
  int index = rand() % potentialMoves.size();
  tuple<tuple<S8, S8>, tuple<S8, S8>> theMove = potentialMoves[index];
  tuple<S8, S8> src = get<0>(theMove);
  tuple<S8, S8> dest = get<1>(theMove);
  S8 srcRow = get<0>(src);
  S8 srcCol = get<1>(src);
  S8 destRow = get<0>(dest);
  S8 destCol = get<1>(dest);

  AI::makeMove(srcRow, srcCol, destRow, destCol);
}
