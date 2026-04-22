#include "AIPlayer.h"
#include <cstdlib>

AIPlayer::AIPlayer(const std::string& name, int color) : name(name), color(color) {}

std::pair<int, int> AIPlayer::getMove()
{
    // random move
    int x = rand() % 8;
    int y = rand() % 8;

    return std::pair(x, y);
};