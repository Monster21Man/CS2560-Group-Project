#include "AIPlayer.h"
#include <cstdlib>

AIPlayer::AIPlayer(const std::string& name, int color) : Player(name, color){}

std::pair<int, int> AIPlayer::getMove(const Board& board)
{
    //AI chooses move based off how many spaces it can flip
    int maxFlips = -1;
    std::pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            auto flips = board.getFlips(i, j, getColor());
            if ((int)flips.size() > maxFlips)
            {
                maxFlips = flips.size();
                bestMove = {i, j};
            }
        }
    }

    return bestMove;
};