#include "game.h"

Game game;

int main(void) {
    init_game(&game, "Pong", 650, 650);

    setup(&game);

    while(game.is_running) {
        handle_input(&game);
        update(&game);
        render(&game);
    }

    return 0;
}
