#pragma once
#include <string>

class Player {
public:
    Player(const std::string& name, int color);

    std::string getName() const;
    int getColor() const;

    virtual std::pair<int, int> getMove(); 

    virtual ~Player() = default;

private:
    std::string name;
    int color;
};