#include "../include/game_manager.hpp"
#include "../include/life.hpp"

int main(int argc, char *argv[]) {
    life::GameManager game;

    if (!game.initialize_game(argc, argv))
        return 1;

    while (not game.game_over()) {        
        game.render();
        game.evolve();
    }

    return 0;
}