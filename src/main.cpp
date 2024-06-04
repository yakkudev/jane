#include "game.h"

int main() {
    Game game(800, 600, "gravity demo | press R to reset scene");
    game.init();
    game.run();

    return 0;
}