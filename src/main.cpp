#include "../include/game_manager.hpp"
#include "../include/life.hpp"

int main(int argc, char *argv[]) {
    life::GameManager game;

    game.initialize_game(argc, argv);

    while (not game.game_over()) {
        game.evolve();
        game.render();
    }

    return 0;
}