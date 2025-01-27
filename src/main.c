#include "game.h"

Game game;

int main(void) {
    init_game(&game, "Pong", 650, 650);

    while(game.is_running) {
        render(&game);
    }

    return 0;
}
