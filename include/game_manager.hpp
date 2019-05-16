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
        int rows, cols, gen = 1;

        public:
        GameManager() {};

        void encode_png(const char* filename, const unsigned char * image, unsigned width, unsigned height);
        bool save_ppm3( const unsigned char * data, size_t w, size_t h, size_t d,  const std::string & file_name_ );

        void initialize_game(int argc, char *argv[]);
        bool game_over();
        void evolve ();
        void render ();
    };
}

#endif