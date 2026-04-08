#include "Board.h"

Board::Board() {
    reset();
}

void Board::reset() {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            grid[r][c] = EMPTY;
        }
    }
    grid[3][3] = WHITE;
    grid[3][4] = BLACK;
    grid[4][3] = BLACK;
    grid[4][4] = WHITE;
}

int Board::getCell(int row, int col) const {
    return grid[row][col];
}

bool Board::isInBounds(int row, int col) const {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

std::vector<std::pair<int,int>> Board::getFlips(int row, int col, int player) const {
    if (grid[row][col] != EMPTY) return {};
 
    std::vector<std::pair<int,int>> allFlips;
    int opp = (player == BLACK) ? WHITE : BLACK;
 
    for (auto& dir : Directions) {
        int dr = dir[0], dc = dir[1];
        std::vector<std::pair<int,int>> lineFlips;
 
        int r = row + dr;
        int c = col + dc;
 
        while (isInBounds(r, c) && grid[r][c] == opp) {
            lineFlips.push_back({r, c});
            r += dr;
            c += dc;
        }
 
        if (!lineFlips.empty() && isInBounds(r, c) && grid[r][c] == player) {
            allFlips.insert(allFlips.end(), lineFlips.begin(), lineFlips.end());
        }
    }
 
    return allFlips;
}

bool Board::isValidMove(int row, int col, int player) const {
    return !getFlips(row, col, player).empty();
}

bool Board::applyMove(int row, int col, int player) {
    auto flips = getFlips(row, col, player);
    if (flips.empty()) return false;

    grid[row][col] = player;
    for (auto& [row, col] : flips) {
        grid[row][col] = player;
    }
    return true;
}

bool Board::hasValidMove(int player) const {
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (isValidMove(r, c, player)) return true;
        }
    }
    return false;
}

int Board::countPieces(int player) const {
    int count = 0;
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < BOARD_SIZE; c++) {
            if (grid[r][c] == player) count++;
        }
    }
    return count;
}