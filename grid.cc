#include "grid.h"
#include "piece.h"
#include <iostream>

using namespace std;

Grid::Grid(Xwindow &w) : w(w)
{
    for (S8 i = 0; i < GRID_SIZE; ++i)
    {
        for (S8 j = 0; j < GRID_SIZE; ++j)
        {
            theGrid[i][j].setCoords(i, j, &w);
        }
    }
}

S8 Grid::getSize()
{
  return GRID_SIZE;
}

Piece::WPtr Grid::getPiece(S8 row, S8 col)
{
  return theGrid[row][col].getPiece();
}

void Grid::addPiece(Piece::SPtr piece, S8 row, S8 col)
{
    theGrid[row][col].setPiece(piece);
}

void Grid::movePiece(S8 srcRow, S8 srcCol, S8 destRow, S8 destCol)
{
    Piece::WPtr piece = theGrid[srcRow][srcCol].getPiece();
    if (Piece::SPtr sPiece = piece.lock())
    {
        theGrid[srcRow][srcCol].setPiece(nullptr);
        theGrid[destRow][destCol].setPiece(sPiece);
    }
    else
    {
        cout << "failed to lock" << endl;
    }
}

void Grid::notifyDisplay(S8 row, S8 col)
{
  theGrid[row][col].draw();
}

