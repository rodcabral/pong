#ifndef _GAME_H_
#define _GAME_H_

#define WINDOW_WIDTH 650
#define WINDOW_HEIGHT 650

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;

    int is_running;
} Game;

bool init_game(Game* game, const char* title, int winW, int winH);

void handle_input(Game* game);

void update(Game* game);

void render(Game* game);

#endif
