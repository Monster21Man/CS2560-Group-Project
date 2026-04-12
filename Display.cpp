#include "Display.h"

Display::Display(const char* name, int width, int height)
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

Display::~Display()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Display::update()
{
    SDL_RenderPresent(renderer);
}

void Display::clear()
{
    SDL_RenderClear(renderer);
}

void Display::setClearColor(const SDL_Color& color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Display::draw(SDL_Rect* rect, const SDL_Color& color, bool fill)
{
    setClearColor(color);
    (fill) ? SDL_RenderFillRect(renderer, rect) : SDL_RenderDrawRect(renderer, rect);
}

void Display::draw(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dst)
{
    SDL_RenderCopy(renderer, texture, src, dst);
}

void Display::draw(const char* text, TTF_Font* font, int x, int y, u_char r, u_char g, u_char b, u_char a)
{
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, {r, g, b, a});
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    int rectWidth, rectHeight;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &rectWidth, &rectHeight);
    SDL_Rect dst = {x, y, rectWidth, rectHeight};

    draw(textTexture, nullptr, &dst);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

SDL_Renderer* Display::getRenderer()
{
    return renderer;
}