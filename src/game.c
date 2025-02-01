#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_video.h>
#include "game.h"
#include "object.h"
#include "load_font.h"

Object player, adversary, ball;

const int p_width = 10;
const int p_height = 100;
const int p_gap = 18;

int base_speed = 10;
int ball_base_speed = 6;

int ballX = 5;
int ballY = 3;

int check = 1;

int player_score, adversary_score = 0;

void reset_pos() {
    ball.rect.x = WINDOW_WIDTH / 2;
    ball.rect.y = rand() % WINDOW_HEIGHT - ball.rect.h;

    ballY = 2;
    if(check) {
        ballX = -2;
    } else {
        ballX = 2;
    }
}

void handle_ball() {
    ball.rect.x += ballX;
    ball.rect.y += ballY;

    if(ball.rect.x >= WINDOW_WIDTH - ball.rect.w) {
        check = 1;

        player_score++;
        reset_pos();
    }

    if(ball.rect.x <= 0) {
        check = 0;

        adversary_score++;
        reset_pos();
    } 

    if(ball.rect.y <= 0) {
        ballY = ball_base_speed;
    }

    if(ball.rect.y >= WINDOW_HEIGHT - ball.rect.h) {
        ballY = ball_base_speed * -1;
    }
}

void check_hit(Object* object) {
        int where_hit = object->rect.y + object->rect.h - ball.rect.y;

        if (where_hit >= 0 && where_hit < 7) {
            ballY = 4;
        }

        if (where_hit >= 7 && where_hit < 14) {
            ballY = 3;
        }
        
        if (where_hit >= 14 && where_hit < 21) {
            ballY = 2;
        }

        if (where_hit >= 21 && where_hit < 28) {
            ballY = 1;
        }

        if (where_hit >= 28 && where_hit < 32) {
            ballY = 0;
        }

        if (where_hit >= 32 && where_hit < 39) {
            ballY = -1;
        }

        if (where_hit >= 39 && where_hit < 46) {
            ballY = -2;
        }

        if (where_hit >= 46 && where_hit < 53) {
            ballY = -3;
        }

        if (where_hit >= 53 && where_hit <= 60) {
            ballY = -4;
        }
}

void handle_player() {
    if((ball.rect.x <= player.rect.x + player.rect.w) && (ball.rect.y >= player.rect.y) && (ball.rect.y <= player.rect.y + player.rect.h)) {
        ballX = ball_base_speed;
        ballY = ball_base_speed  * -1;

        check_hit(&player);        
    }
}

void handle_adversary() {
    if((ball.rect.x >= adversary.rect.x - adversary.rect.w) && (ball.rect.y >= adversary.rect.y) && (ball.rect.y <= adversary.rect.y + adversary.rect.h)) {
        ballX = ball_base_speed * -1;
        ballY = ball_base_speed * -1;

        check_hit(&adversary);
    }

    if(ball.rect.y + ball.rect.h >= WINDOW_HEIGHT / 2) {
        adversary.rect.y += base_speed;
    } else {
        adversary.rect.y -= base_speed;
    }

    if(adversary.rect.y <= 0) {
        adversary.rect.y = 0;
    }

    if(adversary.rect.y + adversary.rect.h > WINDOW_HEIGHT) {
        adversary.rect.y = WINDOW_HEIGHT - adversary.rect.h;
    }
}

bool init_game(Game* game, const char* title, int winW, int winH) {
    srand(time(NULL));

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) { 
        
        fprintf(stderr, "Could not initialize SDL\n");

        return false;
    }

    TTF_Init();

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

    player = init_object(game->renderer, 0, 0, p_width, p_height);
    adversary = init_object(game->renderer, 0, 0, p_width, p_height);
    ball = init_object(game->renderer, 0, 0, 15, 15);

    player.rect.x = p_gap; 
    player.rect.y = (WINDOW_HEIGHT / 2) - p_height / 2;

    adversary.rect.x = WINDOW_WIDTH - p_gap - p_width;
    adversary.rect.y = (WINDOW_HEIGHT / 2) - p_height / 2;

    reset_pos();

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
        player.rect.y -= base_speed;

        if(player.rect.y <= 0) {
            player.rect.y = 0;
        }
    }

    if(keys[SDL_SCANCODE_DOWN]) {
        player.rect.y += base_speed;

        if(player.rect.y + player.rect.h > WINDOW_HEIGHT) {
            player.rect.y = WINDOW_HEIGHT - player.rect.h;
        }
    }
}

void update(Game* game) {
    handle_ball();

    handle_player();

    handle_adversary(); 

    if(player_score == 10) {
        printf("Player won!\n");
        game->is_running = false;
    }

    if(adversary_score == 10) {
        printf("Adversary won!\n");
        game->is_running = false;
    }
}

void render(Game* game) {
    SDL_SetRenderDrawColor(game->renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(game->renderer);

    for(int i = 1; i < WINDOW_HEIGHT / 26; ++i) {
        SDL_Rect rect = {
            .x = WINDOW_WIDTH / 2 + 8 / 2,
            .y = i * 26,
            .w = 5,
            .h = 13,
        };
        SDL_SetRenderDrawColor(game->renderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderFillRect(game->renderer, &rect);
    }

    render_object(&player);
    render_object(&adversary);
    render_object(&ball);

    char f_buffer[1000];
    snprintf(f_buffer, 1000, "%d", player_score);
    load_font(game->renderer, "fonts/dogicapixel.ttf", f_buffer, 50, WINDOW_WIDTH / 2 - 32 - 50, 20);

    snprintf(f_buffer, 1000, "%d", adversary_score);
    load_font(game->renderer, "fonts/dogicapixel.ttf", f_buffer, 50, WINDOW_WIDTH / 2 + 50, 20);

    SDL_RenderPresent(game->renderer);
}
