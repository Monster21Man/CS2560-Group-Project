#include "Game.h"
#include "Player.h"
#include "Display.h"

int main() {
    Player black("Player 1", BLACK);
    Player white("Player 2", WHITE);

    Game game(&black, &white);


    //TODO: Implement game loop and display logic

    game.run();

    return 0;
}