#include "setup.h"
#include <iostream>
#include <memory>
#include <string>
#include <locale>

#include "gameManager.h"
#include "grid.h"
#include "player.h"

class Piece;
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"

using namespace std;

static const string INVALID_BOARD = "Invalid board configuration, cannot exit setup.";
static const string INVALID_INPUT = "Invalid input. Enter setup command again.";

void Setup::addPiece()
{
  char colour = 'b';
  S8 row;
  S8 col;
  char type;

  Piece::SPtr toAdd;

  cin >> type;
  if (isupper(type)) // uppercase letters represent white pieces
  {
    colour = 'w';
    type = tolower(type);
  }

  // input format is [a-h][1-8] ie. e5
  cin >> col;
  cin >> row;

  if (isupper(col))
  {
    col = tolower(col);
  }

  col -= 'a'; // convert letter to int
  row -= '1';

  if (row < 0 || row > 7 || col < 0 || col > 7)
  {
    cerr << INVALID_INPUT << endl;
    return;
  }

  switch (type)
  {
    case 'b':
      toAdd = Piece::SPtr(new Bishop(colour));
      break;
    case 'k':
      toAdd = Piece::SPtr(new King(colour));
      break;
    case 'n':
      toAdd = Piece::SPtr(new Knight(colour));
      break;
    case 'p':
      toAdd = Piece::SPtr(new Pawn(colour));
      break;
    case 'q':
      toAdd = Piece::SPtr(new Queen(colour));
      break;
    case 'r':
      toAdd = Piece::SPtr(new Rook(colour));
      break;
    default:
      cerr << INVALID_INPUT << endl;
      cin.clear();
      cin.ignore(10000, '\n');
      return;
  }

  GameManager::getInstance().addPiece(toAdd, row, col);
  GameManager::getInstance().notifyDisplay(row, col);
}

void Setup::deletePiece()
{
  S8 row, col;
  cin >> col;
  col -= 'a'; // convert letter to int
  if (col < 0 || col > 7) {
    cerr << INVALID_INPUT << endl; // out of bounds
    cin.clear();
    cin.ignore(10000, '\n');
    return;
  }
  cin >> row;
  row -= '1';
  if (row < 0 || row > 7) {
    cerr << INVALID_INPUT << endl; // out of bounds
    cin.clear();
    cin.ignore(10000, '\n');
    return;
  }

  GameManager::getInstance().destroyPiece(row, col);
  GameManager::getInstance().notifyDisplay(row, col);
}

// changeColour: changes the colour of the starting player
void Setup::changeColour(char &colour)
{
  char newColour;
  cin >> newColour;
  if (newColour != 'w' && newColour != 'b')
  {
    cerr << "Not a valid colour" << endl;
    cin.clear();
    cin.ignore(10000, '\n');
    return;
  }
  colour = newColour;
}

// setup function, called by main
void Setup::setBoard(char &colour)
{
  char c;

  while (cin >> c) {

    switch(c)
    {
      case '+':
        addPiece();
        break;
      case '-':
        deletePiece();
        break;
      case '=':
        changeColour(colour);
        break;
      case 'd': // done
        if (GameManager::getInstance().isValidBoard())
        {
          return;
        }
        cerr << INVALID_BOARD << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        break;
      default:
        cerr << INVALID_INPUT << endl;
        cin.clear();
        cin.ignore(10000, '\n');
        break;
    }
  }
}

void Setup::setDefaultBoard()
{
  shared_ptr<Piece> toAdd;
  GameManager &gm = GameManager::getInstance();

  // initialize white pieces
  for (int i = 0; i < 8; i++) {// pawns
    toAdd = shared_ptr<Piece>(new Pawn('w'));
    gm.addPiece(toAdd, 6, i);
  }
  for (int i = 0; i < 2; i++) {// rooks
    toAdd = shared_ptr<Piece>(new Rook('w'));
    gm.addPiece(toAdd, 7, 0 + 7*i);
  }
  for (int i = 0; i < 2; i++) { // knights
    toAdd = shared_ptr<Piece>(new Knight('w'));
    gm.addPiece(toAdd, 7, 1 + 5*i);
  }
  for (int i = 0; i < 2; i++) { // bishops
    toAdd = shared_ptr<Piece>(new Bishop('w'));
    gm.addPiece(toAdd, 7, 2 + 3*i);
  }
  toAdd = shared_ptr<Piece>(new Queen('w'));
  gm.addPiece(toAdd, 7, 3);

  toAdd = shared_ptr<Piece>(new King('w'));
  gm.addPiece(toAdd, 7, 4);
  gm.setKing(toAdd);

  // initialize black pieces
  for (int i = 0; i < 8; i++) {// pawns
    toAdd = shared_ptr<Piece>(new Pawn('b'));
    gm.addPiece(toAdd, 1, i);
  }
  for (int i = 0; i < 2; i++) {// rooks
    toAdd = shared_ptr<Piece>(new Rook('b'));
    gm.addPiece(toAdd, 0, 0 + 7*i);
  }
  for (int i = 0; i < 2; i++) { // knights
    toAdd = shared_ptr<Piece>(new Knight('b'));
    gm.addPiece(toAdd, 0, 1 + 5*i);
  }
  for (int i = 0; i < 2; i++) { // bishops
    toAdd = shared_ptr<Piece>(new Bishop('b'));
    gm.addPiece(toAdd, 0, 2 + 3*i);
  }
  toAdd = shared_ptr<Piece>(new Queen('b'));
  gm.addPiece(toAdd, 0, 3);

  toAdd = shared_ptr<Piece>(new King('b'));
  gm.addPiece(toAdd, 0, 4);
  gm.setKing(toAdd);

  for (S8 i = 0; i < 8; ++i)
  {
    for (S8 j = 0; j < 8; ++j)
    {
      gm.notifyDisplay(i, j);
    }
  }
}

bool Setup::setPlayers()
{
  string input;
  char c;
  cin >> input;
  c = input.at(0);
  U8 wLevel = 0;
  U8 bLevel = 0;

  if (c == 'h')
  {
    wLevel = 0;
  }
  else if (c == 'c')
  {
    c = input.at(input.length() - 1); // last char of string
    wLevel = c - '0';
  }

  cin >> input;
  c = input.at(0);
  if (c == 'h')
  {
    bLevel = 0;
  }
  else if (c == 'c')
  {
    c = input.at(input.length() - 1);
    bLevel = c - '0';
  }
  cout << (int)wLevel << " " << (int)bLevel << endl;

  return (Player::setWhite(wLevel) && Player::setBlack(bLevel));
}

