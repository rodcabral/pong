#include "game.h"

Game game;

int main(void) {
    init_game(&game, "Pong", WINDOW_WIDTH, WINDOW_HEIGHT);

    const int FPS = 60;
    const int frame_delay = 1000 / FPS;

    Uint32 frame_start;
    int frame_time;

    while(game.is_running) {
        frame_start = SDL_GetTicks();
        handle_input(&game);
        update(&game);
        render(&game);

        frame_time = SDL_GetTicks() - frame_start;

        if(frame_delay > frame_time) {
            SDL_Delay(frame_delay - frame_time);
        }
    }

    return 0;
}
