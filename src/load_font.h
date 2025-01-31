#ifndef _LOAD_FONT_H_
#define _LOAD_FONT_H_

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

void load_font(SDL_Renderer* renderer, const char* src, const char* data, int size, int x, int y);

#endif
