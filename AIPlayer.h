#pragma once
#include <string>
#include "Player.h"


class AIPlayer : public Player
{
public:
    AIPlayer(const std::string& name, int color);

    std::pair<int, int> getMove() override;

private:
    std::string name;
    int color;
};