#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <thread>

#include "life.hpp"
#include "../include/canvas.hpp"
#include "../include/lodepng.h"

namespace life {
    /**
     * @brief A class that runs all game logic.
     * @author Eduardo Sarmento & Victor Vieira
     * 
     * This class has all the logic of the game.
     */
    class GameManager
    {
        private:
        std::vector<life::Life> log;    //!< Vector that stores all generations for stability checking.
        int rows;                       //!< Number of game space's rows.
        int cols;                       //!< Number of game space's columns.
        int gen = 0;                    //!< Current generation.

        /// Stores all default and/or user-given settings of the simulation.
        struct game_settings {
            char *imgdir = nullptr;             //!< Directory where output images are written to.
            int maxgen = -1;                    //!< Maximum number of generations to simulate.
            int fps = -1;                       //!< Number of generations presented per second.
            int blocksize = 5;                  //!< Pixel size of a cell.
            Color bkgcolor = GREEN;             //!< Color name for the background.
            Color alivecolor = RED;             //!< Color name for representing alive cells.
            char *outfile;                      //!< Filename to write text output.
            char *input_cfg_file = nullptr;     //!< Path to the input.
        } settings;

        public:
        /// Default constructor that does nothing.
        GameManager() {};

        /*! Generates a PNG image using LodePNG.
         *
         * @param filename Path with the name of image to be generated.
         * @param image Image data.
         * @param width Width of the image.
         * @param height Height of the image.
         */
        void encode_png(const char* filename, const unsigned char * image, unsigned width, unsigned height);
        
        /*! Returns a color with the name given. Returns BLACK if there is no correspondence.
         *
         * @param string A string with the color name.
         */
        Color stringToColor (char *string);

        /// Checks if current generation is equals to any past generation.
        bool stable ();
        
        /*! Reads all settings given by the user and tries to create a new simulation.
         * 
         * @param argc Number of command line arguments.
         * @param argv Command line arguments.
         */
        bool initialize_game(int argc, char *argv[]);

        /// Checks if the simulation is stable, extinct or reached the maximum amount of generations.
        bool game_over();
        /// Apply game rules to the last generation and generates a new one.
        void evolve ();
        /// Wait time corresponding to the frame rate given by the user.
        void wait();
        /// Generates images, writes text files and prints outputs.
        void render ();
        /// Prints help text.
        void print_help();
    };
}

#endif