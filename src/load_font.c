#include "load_font.h"

void load_font(SDL_Renderer* renderer, const char *src, const char* data, int size, int x, int y) {
    TTF_Font* opened_font = TTF_OpenFont(src, size);

    renderer = renderer;

    SDL_Color color = {
        .r = 0xff,
        .g = 0xff,
        .b = 0xff,
        .a = 0xff
    };

    SDL_Surface* font_surface = TTF_RenderText_Blended(opened_font, data, color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, font_surface);

    SDL_Rect dest;

    dest.w = font_surface->w;
    dest.h = font_surface->h;

    dest.x = x;
    dest.y = y;

    SDL_FreeSurface(font_surface);
    TTF_CloseFont(opened_font);

    SDL_RenderCopy(renderer, texture, NULL, &dest);

    SDL_DestroyTexture(texture);
}
