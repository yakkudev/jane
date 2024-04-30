#include "game.h"

int main() {
    Game game(800, 600, "JANE!");
    game.init();
    game.run();

    return 0;
}