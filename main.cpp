#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"
#include "Player.h"
#include "Display.h"

// ---------- circle helper ----------
void drawCircle(SDL_Renderer* renderer, int cx, int cy, int radius)
{
    for (int x = -radius; x <= radius; x++)
    {
        for (int y = -radius; y <= radius; y++)
        {
            if (x*x + y*y <= radius*radius)
            {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

int main(int argc, char* argv[])
{
    Player black("Player 1", BLACK);
    Player white("Player 2", WHITE);

    Game game(&black, &white);
    Board& board = const_cast<Board&>(game.getBoard());

    Display display("Reversi", 640, 640);

    bool running = true;
    SDL_Event e;

    int tileSize = 80;
    SDL_Renderer* renderer = display.getRenderer();

    while (running)
    {
        // ---------------- INPUT ----------------
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = false;

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int col = e.button.x / tileSize;
                int row = e.button.y / tileSize;

                Player* current = game.getCurrentPlayer();
                int color = current->getColor();

                if (board.applyMove(row, col, color))
                {
                    game.switchTurnPublic();
                }
                else
                {
                    std::cout << "Invalid move\n";
                }
            }
        }

        // ---------------- DRAW ----------------
        display.setClearColor({0, 150, 0, 255});
        display.clear();

        // grid
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        for (int i = 0; i <= 8; i++)
        {
            SDL_RenderDrawLine(renderer, i * tileSize, 0, i * tileSize, 640);
            SDL_RenderDrawLine(renderer, 0, i * tileSize, 640, i * tileSize);
        }

        // pieces from board (NOW CIRCLES)
        for (int r = 0; r < 8; r++)
        {
            for (int c = 0; c < 8; c++)
            {
                int cell = board.getCell(r, c);
                if (cell == EMPTY) continue;

                if (cell == BLACK)
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                else
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                int cx = c * tileSize + tileSize / 2;
                int cy = r * tileSize + tileSize / 2;
                int radius = tileSize / 2 - 10;

                drawCircle(renderer, cx, cy, radius);
            }
        }

        display.update();
    }

    return 0;
}