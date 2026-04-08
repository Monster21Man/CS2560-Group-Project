#pragma once
#include "Board.h"
#include "Player.h"

enum class GameState {
    ONGOING,
    BLACK_WINS,
    WHITE_WINS,
    DRAW
};

class Game {
public:
    Game(Player* blackPlayer, Player* whitePlayer);
    void run();
    GameState checkWinCondition() const;

    Player* getCurrentPlayer() const;

    const Board& getBoard() const;

private:
    Board board;
    Player* players[2]; // index 0 = BLACK, index 1 = WHITE
    int currentPlayerIndex;
 
    void switchTurn();
};