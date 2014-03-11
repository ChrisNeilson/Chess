#include "ai1.h"
#include "bishop.h"
#include "queen.h"
#include "knight.h"
#include "rook.h"
#include "gameManager.h"
#include <cstdlib>
#include <tuple>
#include <vector>

using namespace std;

AIOne::AIOne(char colour): AI(colour) {}

U8 AIOne::getType()
{
  return 1;
}

void AIOne::makeMove()
{
  clearEnPassant();
  vector<Piece::SPtr> untriedPieces(pieces_);
  srand(time(NULL));

  // Randomly go through all possible pieces
  for (;;)
  {
    int randPieceIndex = rand() % untriedPieces.size();
    Piece::SPtr piece = untriedPieces[randPieceIndex];

    vector<tuple<S8, S8>> untriedMoves(gm_.getPossibleMoves());
    // Randomly attempt each possible move.
    while (untriedMoves.size() > 0)
    {
      int randMoveIndex = rand() % untriedMoves.size();
      tuple<S8, S8> move = untriedMoves[randMoveIndex];

      S8 destRow = get<0>(move);
      S8 destCol = get<1>(move);

      // If move is valid, make it, we're done
      if (gm_.isValidMove(piece, destRow, destCol))
      {
        AI::makeMove(piece->getRow(), piece->getCol(), destRow, destCol);
        return;
      }
      // Erase the move we tried
      else
      {
        untriedMoves.erase(untriedMoves.begin() + randMoveIndex);
      }
    }
    // Erase piece that was just tried
    untriedPieces.erase(untriedPieces.begin() + randPieceIndex);
  }
}
