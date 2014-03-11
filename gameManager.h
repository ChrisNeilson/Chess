#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "grid.h"
#include "types.h"
#include "window.h"

#include <vector>

class Piece;

class GameManager
{
  private:
    static GameManager instance;

    Xwindow xw;
    Grid grid;
    std::vector<std::shared_ptr<Piece>> bPieces_;
    std::vector<std::shared_ptr<Piece>> wPieces_;

    std::vector<std::tuple<S8, S8>> possibleMoves_;

    GameManager();

    bool hasValidMove(char colour);

  public:
    static GameManager &getInstance();
    std::shared_ptr<Piece> bKing_;
    std::shared_ptr<Piece> wKing_;

    Xwindow &getWindow();
    std::shared_ptr<Piece> getPiece(S8 row, S8 col);
    std::vector<std::shared_ptr<Piece>> &getBlackPieces();
    std::vector<std::shared_ptr<Piece>> &getWhitePieces();
    std::vector<std::tuple<S8, S8>> getPossibleMoves();
    std::string getStatus(char colour); // colour is the player who moves NEXT

    void clearPieces();
    void notifyDisplay(S8 row, S8 col);

    void addPiece(std::shared_ptr<Piece> piece, S8 row, S8 col);
    void destroyPiece(S8 row, S8 col);
    void movePiece(S8 srcRow, S8 srcCol, S8 destRow, S8 destCol);
    void setKing(std::shared_ptr<Piece> king);

    bool arePiecesBetween(std::shared_ptr<Piece> piece, S8 destRow, S8 destCol);
    bool isValidBoard();
    bool isValidMove(std::shared_ptr<Piece>, S8 destRow, S8 destCol);
    bool isCheck(char colour); // colour corresponds to defending pieces
    bool isUnderAttack(std::shared_ptr<Piece> piece);
};

#endif
