#include <SDL2/SDL_video.h>
#include "game.h"
#include "object.h"

Object example;

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

    example = init_object(game->renderer, 10, 10, 20, 20); 

    game->is_running = true;

    return true;
}

void handle_input(Game* game) {
    SDL_Event event;

    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            game->is_running = false;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    game->is_running = false;
                    break;
            }
            break;
    }
}

void update() {
    example.rect.x++;
}

void render(Game* game) {
    SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(game->renderer);

    render_object(&example);

    SDL_RenderPresent(game->renderer);
}
