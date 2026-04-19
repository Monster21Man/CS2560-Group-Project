#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class Display
{
    public:
        Display(const char* name, int width, int height);
        ~Display();

        void update();
        void clear();
        void setClearColor(const SDL_Color& color);
        void draw(SDL_Rect* rect, const SDL_Color& color, bool fill = true);
        void draw(SDL_Texture* texture, SDL_Rect* src = nullptr, SDL_Rect* dst = nullptr);
        void draw(const char* text, TTF_Font* font, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    
        SDL_Renderer* getRenderer();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
};