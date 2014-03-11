#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "gameManager.h"
#include "setup.h"
#include "types.h"

#include "player.h"
#include "grid.h"

#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include <memory>
#include "window.h"

using namespace std;

int main()
{
  GameManager &gm = GameManager::getInstance();
  U32 whiteScore = 0;
  U32 blackScore = 0;
  bool customSetup = false;
  bool gameInProgress = false;
  char nextTurn = 'w'; // white goes first

  string status;
  string input;
  char inChar;

  while(cin >> input)
  {
    inChar = input[0];

    switch(inChar)
    {
      case 's':
        if (gameInProgress)
        {
          cerr << "Can't setup while game is running. Enter new command." << endl;
          break;
        }
        Setup::setBoard(nextTurn);

        customSetup = true;
        break;

      case 'g':
        if (gameInProgress)
        {
          cerr << "Can't start game while game in progress. Enter new command." << endl;
          break;
        }
        if (!Setup::setPlayers())
        {
          cerr << "Failed to setup players" << endl;
          break;
        }

        if (!customSetup)
        {
          Setup::setDefaultBoard();
        }

        gameInProgress = true;
        break;

      case 'm':
        if (!gameInProgress)
        {
          cerr << "Can't make move when game is not running. Enter new command." << endl;
          break;
        }
        if (nextTurn == 'w')
        {
          cout << "white move" << endl;
          Player::getWhite()->makeMove();
        }
        else
        {
          cout << "black move" << endl;
          Player::getBlack()->makeMove();
        }
        cout << "outa there" << endl;
        nextTurn = nextTurn == 'w' ? 'b' : 'w';

        status = GameManager::getInstance().getStatus(nextTurn);
        if (status == "Check")
        {
          if (nextTurn == 'w')
          {
            cout << "White is in check." << endl;
          }
          else
          {
            cout << "Black is in check." << endl;
          }
        }
        else if (status == "CheckMate")
        {
          if (nextTurn == 'w')
          {
            cout << "Checkmate! Black wins!" << endl;
            blackScore += 2;
          }
          else
          {
            cout << "Checkmate! White wins!" << endl;
            whiteScore += 2;
          }
          cout << "Press any key to continue" << endl;
          getline(cin, input);
          getline(cin, input);

          // cleanup and reset
          GameManager::getInstance().clearPieces();
          customSetup = false;
          nextTurn = 'w';
          gameInProgress = false;
        }
        else if (status == "StaleMate")
        {
          cout << "Stalemate!" << endl;

          whiteScore++;
          blackScore++;
          cout << "Press any key to continue" << endl;
          getline(cin, input);
          getline(cin, input);
          // cleanup and reset
          GameManager::getInstance().clearPieces();
          nextTurn = 'w';
          customSetup = false;
          gameInProgress = false;
        }
        break;

      case 'r':
        if (!gameInProgress)
        {
          cerr << "Can't resign game if not in progress. Enter a new command." << endl;
          break;
        }
        if (nextTurn == 'w')
        {
          cout << "Black wins!" << endl;
          blackScore += 2;
        }
        else
        {
          cout << "White wins!" << endl;
          whiteScore += 2;
        }
        // cleanup and reset
        GameManager::getInstance().clearPieces();
        nextTurn = 'w';
        customSetup = false;
        break;
      default:
        // invalid input
        cerr << "Invalid command. Enter command again." << endl;
        break;
    }
  }

  return 0;
}
