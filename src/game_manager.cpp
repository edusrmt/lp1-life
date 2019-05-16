#include "../include/game_manager.hpp"
#include "../include/visor.hpp"
#include "../include/life.hpp"

using namespace life;

void GameManager::initialize_game(int argc, char *argv[])
{
    std::ifstream input;
    input.open(argv[1]);

    int r, c;
    char alive;
    std::string line;

    input >> r >> c;
    input >> alive;

    while (input >> line) {
        if (line.size() < (size_t)c) {
            // Leia os que tiver e inteire com morto
        }
        else if (line.size() >= (size_t)c) {
            // Leia c caracteres
        }
    }


    state = Life(r,c);

    /*if (argc <= 2 && !strcmp(argv[1], "-h"))
    {
        visor::display_help();
    } else if (argc <= 2) {
        input.open(argv[1]);
    }*/
    
    

    input.close();
}

bool GameManager::game_over () {
    return state.stable() || state.extinct();
}