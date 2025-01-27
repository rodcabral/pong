#include "game.h"
#include <SDL2/SDL_video.h>

bool init_game(Game* game, const char* title, int winW, int winH) {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) { 
        
        fprintf(stderr, "Could not initialize SDL\n");

        return false;
    }

    game->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH, SDL_WINDOW_SHOWN);

    if(!game->window) {
        fprintf(stderr, "Could not create: window\n");

        return false;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, 0);

    if(!game->renderer) {
        fprintf(stderr, "Could not create: renderer\n");

        return false;
    }

    game->is_running = true;

    return true;
}

void render(Game* game) {
    SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(game->renderer);

    SDL_RenderPresent(game->renderer);
}
