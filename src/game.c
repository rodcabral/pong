#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_video.h>
#include "game.h"
#include "object.h"

#define center_bar_total (650 / 8)

Object center_bar[center_bar_total];

Object player, adversary, ball;

bool init_game(Game* game, const char* title, int winW, int winH) {
    srand(time(NULL));

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

    int center_bar_start = 1;
    for(int i = 0; i < center_bar_total; ++i) {
        center_bar[i] = init_object(game->renderer, 325, center_bar_start, 6, 6);
        center_bar_start = (center_bar_start + 8);
    }

    int p_width = 8;
    int p_height = 115;
    int p_gap = 16;

    player = init_object(game->renderer, p_gap, (WINDOW_HEIGHT / 2) - p_height / 2, p_width, p_height);

    adversary = init_object(game->renderer, WINDOW_WIDTH - p_gap - p_width, (WINDOW_HEIGHT / 2) - p_height / 2, p_width, p_height);

    int b_x = WINDOW_WIDTH / 2;
    int b_y = rand() % WINDOW_HEIGHT - ball.rect.h;

    ball = init_object(game->renderer, b_x, b_y, 11, 11);

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

    const Uint8* keys = SDL_GetKeyboardState(NULL);

    if(keys[SDL_SCANCODE_UP]) {
        player.rect.y -= 10;

        if(player.rect.y <= 0) {
            player.rect.y = 0;
        }
    }

    if(keys[SDL_SCANCODE_DOWN]) {
        player.rect.y += 10;

        if(player.rect.y + player.rect.h > WINDOW_HEIGHT) {
            player.rect.y = WINDOW_HEIGHT - player.rect.h;
        }
    }
}

void update() {
}

void render(Game* game) {
    SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(game->renderer);

    for(int i = 0; i < center_bar_total; ++i) {
        render_object(&center_bar[i]);
    }

    render_object(&player);
    render_object(&adversary);
    render_object(&ball);

    SDL_RenderPresent(game->renderer);
}
