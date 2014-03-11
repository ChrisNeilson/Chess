#include <iostream>
#include <limits>
#include <sstream>
#include "bishop.h"
#include "grid.h"
#include "human.h"
#include "knight.h"
#include "queen.h"
#include "rook.h"
#include "gameManager.h"

using namespace std;

string err = "Invalid input. Enter src and end squares again.";
string err2 = "Invalid move. Enter src and end squares again.";

Human::Human(char colour): Player(colour) {}

U8 Human::getType()
{
  return 0;
}

void Human::getMove(S8 &srcRow, S8 &srcCol, S8 &destRow, S8 &destCol)
{
  string src, dest;
  for (;;)
  {
    cin >> src >> dest;

    istringstream is(src);
    char c = is.get();
    if (!isalpha(c)) {
      cout << "1" << endl;
      cerr << err << endl;
      cin.clear();
      cin.ignore();
      continue;
    }
    srcCol = c - 'a';
    c = is.get();
    if (is.fail() || !isdigit(c)) {
      cerr << err << endl;
      cout << "2" << endl;
      cin.clear();
      cin.ignore();
      continue;
    }
    srcRow = (c - '1');

    istringstream is2(dest);
    c = is2.get();
    if (!isalpha(c)) {
      cout << "3" << endl;
      cerr << err << endl;
      cin.clear();
      cin.ignore();
      continue;
    }
    destCol = c - 'a';
    c = is2.get();
    if (is2.fail() || !isdigit(c)) {
      cout << "4" << endl;
      cerr << err << endl;
      cin.clear();
      cin.ignore();
      continue;
    }
    destRow = (c - '1');
    return;
  }
}

void Human::makeMove()
{
  clearEnPassant(); // en passant expires for all of player's pawns
  S8 srcRow, srcCol, destRow, destCol;
  for (;;)
  {
    getMove(srcRow, srcCol, destRow, destCol);

    Piece::SPtr p = gm_.getPiece(srcRow, srcCol);
    if (!p || p->getColour() != colour_)
    {
      cout << colour_ << endl;
      cout << (p == nullptr) << endl;
      cout << "6" << endl;
      cerr << err2 << endl;
      continue;
    }

    if (gm_.isValidMove(p, destRow, destCol))
    {
      Player::executeMove(srcRow, srcCol, destRow, destCol);

      // pawn promotion
      if (p->getType() == Piece::Type::Pawn && ((destRow == 0 && p->getColour() == 'w') ||
          (destRow == 7 && p->getColour() == 'b'))) {
        chooseNewPiece(p);
      }
      cout << srcRow << " " << srcCol << endl;
      cout << destRow << " " << destCol << endl;
      gm_.notifyDisplay(srcRow, srcCol);
      gm_.notifyDisplay(destRow, destCol);
      return;
    }
    else
    { // move not valid
      cout << "7" << endl;
      cerr << err2 << endl;
    }
  }
}

void Human::chooseNewPiece(Piece::SPtr current)
{
  char pieceType;
  cin >> pieceType;

  pieceType = tolower(pieceType); // caps to lcase

  Piece::SPtr newPiece;
  switch(pieceType)
  {
    case 'r':
      newPiece = Piece::SPtr(new Rook(colour_, true));
      break;
    case 'n':
      newPiece = Piece::SPtr(new Knight(colour_));
      break;
    case 'b':
      newPiece = Piece::SPtr(new Bishop(colour_));
      break;
    case 'q':
      newPiece = Piece::SPtr(new Queen(colour_));
      break;
    default:
      // if input char is not {r, n, b, q), then:
      cerr << "Invalid input. Enter piece type again." << endl;
      chooseNewPiece(current);
      return;
  }
  S8 row = current->getRow();
  S8 col = current->getCol();
  gm_.destroyPiece(row, col);
  gm_.addPiece(newPiece, row, col);
}
