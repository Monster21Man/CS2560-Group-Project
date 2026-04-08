#include "Player.h"

Player::Player(const std::string& name, int color) : name(name), color(color) {}

std::string Player::getName() const {
    return name;
}
int Player::getColor() const {
    return color;
}

std::pair<int, int> Player::getMove() {
    // This will be overridden by derived classes (e.g., HumanPlayer, AIPlayer)
    return {-1, -1}; // Invalid move by default
}