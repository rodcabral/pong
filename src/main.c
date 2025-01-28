#include "game.h"

Game game;

int main(void) {
    init_game(&game, "Pong", WINDOW_WIDTH, WINDOW_HEIGHT);

    while(game.is_running) {
        handle_input(&game);
        update();
        render(&game);
    }

    return 0;
}
