#pragma once
#include <vector>
#include <utility>

constexpr int BOARD_SIZE = 8;
constexpr int EMPTY = 0;
constexpr int BLACK = 1;
constexpr int WHITE = 2;

const int Directions[8][2] = {
    {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}
};

class Board {
public:
    Board();
    int getCell(int row, int col) const;
    void reset();
    std::vector<std::pair<int, int>> getFlips(int row, int col, int player) const;
    bool isValidMove(int row, int col, int player) const;
    bool applyMove(int row, int col, int player);
    bool hasValidMove(int player) const;
    int countPieces(int player) const;

private:
    int grid[BOARD_SIZE][BOARD_SIZE];
    bool isInBounds(int row, int col) const;
};