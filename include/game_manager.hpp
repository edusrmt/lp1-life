#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>     // atoi
#include <chrono>
#include <thread>

#include "life.hpp"
//#include "../include/visor.hpp"
#include "../include/canvas.hpp"
#include "../include/lodepng.h"

namespace life {
    class GameManager
    {
        private:
        std::vector<life::Life> log;
        int rows, cols, gen = 0;

        struct game_settings {
            char *imgdir = nullptr;
            int maxgen = -1;
            int fps = -1;
            int blocksize = 5;
            Color bkgcolor = GREEN;
            Color alivecolor = RED;
            char *outfile;
            char *input_cfg_file = nullptr;
        } settings;

        public:
        GameManager() {};

        void encode_png(const char* filename, const unsigned char * image, unsigned width, unsigned height);
        bool save_ppm3( const unsigned char * data, size_t w, size_t h, size_t d,  const std::string & file_name_ );
        Color stringToColor (char *string);

        bool stable ();
        bool initialize_game(int argc, char *argv[]);
        bool game_over();
        void evolve ();
        void wait();
        void render ();
        void print_help();
    };
}

#endif