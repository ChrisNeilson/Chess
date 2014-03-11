#include "ai2.h"
#include "bishop.h"
#include "gameManager.h"
#include "queen.h"
#include "knight.h"
#include "rook.h"
#include <tuple>
#include <vector>

using namespace std;

AITwo::AITwo(char colour): AI(colour) {}

U8 AITwo::getType() { return 2; }

void AITwo::makeMove() {
  /*clearEP(); // En Passant expires
  vector<shared_ptr<Piece>> untriedPieces(pieces);
  srand(time(NULL));
  vector<tuple<tuple<int, int>,tuple<int, int>>> validMoves;

  // Randomly go through all possible pieces
  while(true)
  {
    int randPieceIndex = rand() % untriedPieces.size();
    shared_ptr<Piece> thePiece = untriedPieces[randPieceIndex];
    vector<tuple<int, int>> untriedMoves;
    // Add each possible final move spot
    for (int i = 0; i < 8; ++i)
    {
      for (int j = 0; j < 8; ++j)
      {
        untriedMoves.push_back(make_tuple(i,j));
      }
    }
    // Randomly attempt each possible move.
    while (true && thePiece->getColour() == colour)
    {
      int randMoveIndex = rand() % untriedMoves.size();
      tuple<int, int> theMove = untriedMoves[randMoveIndex];
      int row1 = thePiece->getRow();
      int col1 = thePiece->getCol();
      int row2 = get<0>(theMove);
      int col2 = get<1>(theMove);
      // If move is valid, add to either valid moves or preferred moves
      if (!(row1 == row2 && col1 == col2) && isValidMove(thePiece, row2, col2))
      {
        char c; // Opponent's colour
        if (colour == 'w') c = 'b';
        else c = 'w';
        // put board in final state temporarily
        shared_ptr<Piece> tmp = gm->getPiece(row2, col2);
        gm->removePiece(row2, col2);

        // En Passant
        bool EP = false;
        if (thePiece->getType() == 'p' && abs(col2 - col1) == 1 && !tmp)
        {
          tmp = gm->getPiece(row1, col2);
          gm->removePiece(row1, col2);
          EP = true;
        }

        gm->movePiece(row1, col1, row2, col2);
        bool isCheck = gm->isCheck(c); //opponent in check

        // put the board back
        gm->movePiece(row2, col2, row1, col1);
        if (EP) gm->addPiece(tmp, row1, col2);
        else if (tmp) gm->addPiece(tmp, row2, col2);

        if (!tmp && !isCheck) // not a preferred move
        {
          tuple<int, int> from = make_tuple(row1, col1);
          tuple<int, int> to = make_tuple(row2, col2);
          validMoves.push_back(make_tuple(from, to));
        }
        else // preferred move! make it and we're done
        {
          AI::makeMove(row1, col1, row2, col2);
          return;
        }
      }
      // Erase the move we tried
      untriedMoves.erase(untriedMoves.begin() + randMoveIndex);
      // If there are no moves left, we need to try a new piece
      if (untriedMoves.size() == 0) break;
    }
    // Erase piece that was just tried
    untriedPieces.erase(untriedPieces.begin() + randPieceIndex);

    // No preferred moves. Make a random valid one
    if (untriedPieces.size() == 0)
    {
      tuple<tuple<int, int>, tuple<int, int>> theMove = validMoves[0];
      tuple<int, int> from = get<0>(theMove);
      tuple<int, int> to = get<1>(theMove);
      int row1 = get<0>(from);
      int col1 = get<1>(from);
      int row2 = get<0>(to);
      int col2 = get<1>(to);

      AI::makeMove(row1, col1, row2, col2);
      return;
    }
  }*/
}
