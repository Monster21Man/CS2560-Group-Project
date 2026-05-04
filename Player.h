#pragma once
#include <string>
#include "Board.h"

class Player {
public:
    Player(const std::string& name, int color);

    std::string getName() const;
    int getColor() const;

    virtual std::pair<int, int> getMove(const Board& board);

    virtual ~Player() = default;

protected:
    std::string name;
    int color;
};