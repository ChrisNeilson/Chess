#include "cell.h"
#include "piece.h"
#include "window.h"

using namespace std;

Cell::Cell() : width(62), height(62) {}

Piece::WPtr Cell::getPiece()
{
  return piece;
}

void Cell::setCoords(S8 row, S8 col, Xwindow *w)
{
    this->row = row;
    this->col = col;
    this->window = w;
    this->colour = ((row + col) % 2 == 0) ? 'b' : 'w';
    draw();
}

void Cell::setPiece(Piece::SPtr piece)
{
    if (piece)
    {
      piece->setCoords(row, col);
    }
    this->piece = piece;
}

void Cell::draw() //TODO
{
  if (colour == 'w')
  {
      window->fillRectangle(col*width, row*height, width, height, Xwindow::Orange);
  }
  else
  {
      window->fillRectangle(col*width, row*height, width, height, Xwindow::Brown);
  }

  if (Piece::SPtr sPiece = piece.lock())
  {
    Piece::Type pieceType = sPiece->getType();
    string type;
    switch (pieceType)
    {
      case Piece::Type::Pawn:
        type = "p";
        break;
      case Piece::Type::Rook:
        type = "r";
        break;
      case Piece::Type::Knight:
        type = "n";
        break;
      case Piece::Type::Bishop:
        type = "b";
        break;
      case Piece::Type::Queen:
        type = "q";
        break;
      case Piece::Type::King:
        type = "k";
        break;
    }

    if (sPiece->getColour() == 'w')
    {
      window->drawBigString(col * 62 + 20, (row+1) * 62 - 20, type, Xwindow::White);
    }
    else
    {
      window->drawBigString(col * 62 + 20, (row+1) * 62 - 20, type, Xwindow::Black);
    }
  }
}
