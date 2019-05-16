#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "life.hpp"

namespace life {
    class GameManager
    {
        private:
        life::Life state;

        public:
        GameManager() {};

        void initialize_game(int argc, char *argv[]);
        bool game_over();
    };
}

#endif