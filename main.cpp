#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <iostream>

#include "AIPlayer.h"
#include "Game.h"
#include "Player.h"
#include "Display.h"

const int WIDTH = 640;
const int HEIGHT = 640;

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
    //homescreen
    Display display("Reversi", WIDTH, HEIGHT);
    TTF_Font* font = TTF_OpenFont("Roboto-VariableFont_wdth,wght.ttf", 40);

    bool running = true;
    bool exit = false;
    SDL_Event e;

    SDL_Rect title = {245, 200, 150, 60};
    SDL_Rect button = {225, 280, 190, 60};
    
    while(running)
    {
        //input
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
                case SDL_QUIT:
                    exit = true;
                    running = false;
                    break;
                
                case SDL_MOUSEBUTTONDOWN:
                    if (e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if(e.button.x > button.x && e.button.x < button.x + button.w && 
                           e.button.y > button.y && e.button.y < button.y + button.h)
                        {
                            running = false;
                        }
                    }
                    break;
            }
        }

        //draw
        display.setClearColor({0, 150, 0, 255});
        display.clear();

        display.draw(&title, {0, 0, 0, 255}, false);
        display.draw(&button, {0, 0, 0, 255}, false);

        display.draw("Click Here", font, button.x + 5, button.y + 10, 0, 0, 0, 255);
        display.draw("Reversi", font, title.x + 10, title.y + 5, 0, 0, 0, 255);

        display.update();
    }

    if(exit)
    {
        return 0;
    }
    running = true;

    //game
    Player black("Player 1", BLACK);
    AIPlayer white("Player 2", WHITE);

    Game game(&black, &white);
    Board& board = const_cast<Board&>(game.getBoard());

    int tileSize = 80;
    SDL_Renderer* renderer = display.getRenderer();

    srand(time(0));

    while (running)
    {
        //game
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

                if (current->getColor() != BLACK) break;

                //Human player goes, then AI, repeat
                if (board.applyMove(row, col, BLACK))
                {
                    game.switchTurnPublic();
                    Player* AI = game.getCurrentPlayer();
                    if (AI->getColor() == WHITE)
                    {
                        int AIRow;
                        int AICol;

                        do
                        {
                            auto [r, c] = AI->getMove();
                            AIRow = r;
                            AICol = c;
                        } while (!board.isValidMove(AIRow, AICol, WHITE));

                        board.applyMove(AIRow, AICol, WHITE);
                        game.switchTurnPublic();
                    }
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

    //end game

    TTF_CloseFont(font);

    return 0;
}