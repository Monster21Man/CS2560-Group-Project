#include "Game.h"
#include <iostream>

Game::Game(Player* blackPlayer, Player* whitePlayer) : currentPlayerIndex(0) {
    players[0] = blackPlayer;
    players[1] = whitePlayer;
}

const Board& Game::getBoard() const {
    return board;
}

Player* Game::getCurrentPlayer() const {
    return players[currentPlayerIndex];
}

void Game::switchTurn() {
    currentPlayerIndex = 1 - currentPlayerIndex; // Toggle between 0 and 1
}

GameState Game::checkWinCondition() const {
    int current = getCurrentPlayer()->getColor();
    int next    = (current == BLACK) ? WHITE : BLACK;
 
    bool currentCanMove = board.hasValidMove(current);
    bool nextCanMove    = board.hasValidMove(next);
 
    // Game continues as long as someone can move
    if (currentCanMove || nextCanMove)
        return GameState::ONGOING;
 
    // Neither player can move — count pieces to decide the winner
    int blackCount = board.countPieces(BLACK);
    int whiteCount = board.countPieces(WHITE);
 
    if (blackCount > whiteCount) return GameState::BLACK_WINS;
    if (whiteCount > blackCount) return GameState::WHITE_WINS;
    return GameState::DRAW;
}

void Game::run() {
    while (true) {
        Player* current = getCurrentPlayer();
        int color = current->getColor();
 
        // If this player has no moves, they must pass
        if (!board.hasValidMove(color)) {
            std::cout << current->getName() << " has no moves and must pass.\n";
            switchTurn();
 
            // Check again after the pass
            if (checkWinCondition() != GameState::ONGOING)
                break;
 
            continue;
        }
 
        // Ask the current player for their move
        // (Display should print the board before this point)
        auto [row, col] = current->getMove(/* board */);
 
        if (!board.applyMove(row, col, color)) {
            std::cout << "Invalid move, try again.\n";
            continue; // Don't switch turns on an invalid move
        }
 
        switchTurn();
 
        GameState state = checkWinCondition();
        if (state != GameState::ONGOING)
            break;
    }
 
    // Report result — or delegate to Display if you prefer
    GameState result = checkWinCondition();
    if (result == GameState::BLACK_WINS)
        std::cout << "Black wins!\n";
    else if (result == GameState::WHITE_WINS)
        std::cout << "White wins!\n";
    else
        std::cout << "It's a draw!\n";
}