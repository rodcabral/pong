#ifndef _GAME_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;
} Game;

bool init_game(const char* title, int winW, int winH);

#endif
