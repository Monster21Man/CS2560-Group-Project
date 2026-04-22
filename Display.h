#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class Display
{
    public:
        //constructor, takes in window name, width and height
        Display(const char* name, int width, int height);
        ~Display();

        //updates screen to current render
        void update();
        
        //clears screen to single color
        void clear();

        //set draw color, takes in the color
        void setClearColor(const SDL_Color& color);
        
        //draw rectangle, takes in rect, color, filled or not
        void draw(SDL_Rect* rect, const SDL_Color& color, bool fill = true);
        
        //draw texture, takes in texture to use, Rect source(crop img), Rect destination(where to place and what size)
        void draw(SDL_Texture* texture, SDL_Rect* src = nullptr, SDL_Rect* dst = nullptr);
        
        //draw text, takes in text to draw, font to use, x pos, y pos, red value, green value, blue value, transparency
        void draw(const char* text, TTF_Font* font, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        //get window renderer
        SDL_Renderer* getRenderer();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};