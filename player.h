#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "types.h"

#include <memory>
#include <vector>

class GameManager;
class Piece;

class Player
{
  private:
    static std::unique_ptr<Player> whitePlayer_;
    static std::unique_ptr<Player> blackPlayer_;

  protected:
    char colour_;
    GameManager &gm_;
    std::vector<std::shared_ptr<Piece>> &pieces_;

    Player(char colour);

    bool pawnAtEnd(std::shared_ptr<Piece> p, S8 row, S8 col);
    void clearEnPassant();

  public:
    typedef std::unique_ptr<Player> UPtr;

    virtual ~Player();
    static std::unique_ptr<Player> &getBlack(); // 0 for human, 1+ for AI
    static std::unique_ptr<Player> &getWhite();
    static bool setBlack(U8 playerType);
    static bool setWhite(U8 playerType);

    char getColour();
    void executeMove(S8 srcRow, S8 srcCol, S8 destRow, S8 destCol);

    virtual U8 getType() = 0;
    virtual void makeMove() = 0;
    virtual void chooseNewPiece(std::shared_ptr<Piece> current) = 0;

};

#endif
