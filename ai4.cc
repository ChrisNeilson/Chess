#include "ai4.h"
#include "bishop.h"
#include "gameManager.h"
#include "queen.h"
#include "knight.h"
#include "rook.h"
#include <cstdlib>
#include <limits>
#include <tuple>
#include <vector>

using namespace std;

AIFour::AIFour(char colour): AI(colour) {}

U8 AIFour::getType()
{
  return 4;
}

int AIFour::calcScore(S8 srcRow, S8 srcCol, S8 destRow, S8 destCol)
{
  int score = 0;
  Piece::SPtr piece = gm_.getPiece(srcRow, srcCol);
  U8 val = piece->getValue();

  char c; // Opponent's colour
  if (colour_ == 'w') c = 'b';
  else c = 'w';


  bool isUnderAttackBefore = gm_.isUnderAttack(piece);
  if (isUnderAttackBefore) score += val;

  // put board in final state temporarily
  Piece::SPtr tmp = gm_.getPiece(destRow, destCol);
  gm_.destroyPiece(destRow, destCol);

  // En Passant
  bool EP = false;
  if (piece->getType() == Piece::Type::Pawn && abs(destCol - srcCol) == 1 && !tmp)
  {
    tmp = gm_.getPiece(srcRow, destCol);
    gm_.destroyPiece(srcRow, destCol);
    EP = true;
  }

  if (tmp) score += 2 * (tmp->getValue());

  gm_.movePiece(srcRow, srcCol, destRow, destCol);

  string status = gm_.getStatus(c);
  if (status == "Check") score += 1;
  else if (status == "CheckMate") score += 1000;
  else if (status == "StaleMate") score -= 10;

  cout << "isUnderAttackAfter" << endl;
  bool isUnderAttackAfter = gm_.isUnderAttack(piece);
  cout << "isUnderAttackAfter" << endl;
  if (isUnderAttackAfter) score -= 2 * (piece->getValue());

  // put the board back
  cout << "movingBack" << endl;
  gm_.movePiece(destRow, destCol, srcRow, srcCol);
  if (EP) gm_.addPiece(tmp, srcRow, destCol);
  else if (tmp) gm_.addPiece(tmp, destRow, destCol);
  return score;
}


void AIFour::makeMove()
{
  clearEnPassant();
  vector<Piece::SPtr> untriedPieces(pieces_);
  srand(time(NULL));

  int maxScore = numeric_limits<int>::min();
  vector<tuple<tuple<int, int>,tuple<int, int>>> validMoves;

  // Go through each piece
  for (auto it = untriedPieces.begin(); it != untriedPieces.end(); ++it)
  {
    Piece::SPtr piece = *it;
    vector<tuple<S8, S8>> untriedMoves(gm_.getPossibleMoves());

    // Try each move
    for (vector<tuple<S8, S8>>::iterator it2 = untriedMoves.begin(); it2 != untriedMoves.end();
        ++it2)
    {
      tuple<int, int> move = *it2;
      int srcRow = piece->getRow();
      int srcCol = piece->getCol();
      int destRow = get<0>(move);
      int destCol = get<1>(move);

      // Check if move is valid
      if (gm_.isValidMove(piece, destRow, destCol))
      {
        cout << "valid! " << (int)srcRow << " " << (int)srcCol << " " << (int)destRow << " " << (int)destCol << "****" << endl;
        Piece::SPtr tmp = gm_.getPiece(srcRow, srcCol);
        tmp->getCol();
        int score = calcScore(srcRow, srcCol, destRow, destCol);
        if (score > maxScore)
        {
          validMoves.clear();
          maxScore = score;
        }
        if (score >= maxScore)
        {
          tuple<int, int> from = make_tuple(srcRow, srcCol);
          tuple<int, int> to = make_tuple(destRow, destCol);
          validMoves.push_back(make_tuple(from, to));
        }
      }
    }
  }

  // Choose a random move of maximum score
  int index = rand() % validMoves.size();
  tuple<tuple<int, int>, tuple<int, int>> theMove = validMoves[index];
  tuple<int, int> from = get<0>(theMove);
  tuple<int, int> to = get<1>(theMove);
  int srcRow = get<0>(from);
  int srcCol = get<1>(from);
  int destRow = get<0>(to);
  int destCol = get<1>(to);

  AI::makeMove(srcRow, srcCol, destRow, destCol);
}
