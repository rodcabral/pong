#ifndef _GAME_H_

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_Renderer* renderer;
    SDL_Window* window;

    int is_running;
} Game;

bool init_game(Game* game, const char* title, int winW, int winH);

void setup(Game* game);

void handle_input(Game* game);

void update(Game* game);

void render(Game* game);

#endif
