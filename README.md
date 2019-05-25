# John Conway's Game of Life
## Summary
[1. The Game](#1-The-Game)

[2. Rules](#2-Rules)

[3. Compiling](#3-Compiling)

[4. Game Interface](#4-Game-Interface)

[5. Input File](#5-Input-File)

[6. Authorship](#6-Authorship)

## 1. The Game
The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970.

The game is a zero-player game, meaning that its evolution is determined by its initial state, requiring no further input. One interacts with the Game of Life by creating an initial configuration and observing how it evolves, or, for advanced players, by creating patterns with particular properties.

*Source: [Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life)*

## 2. Rules

The rules in this implementation are:

1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

## 3. Compiling

This project may be compiled with [CMake](https://cmake.org).
CMake is an open-source, cross-platform family of tools designed to build, test and package software.
Basically, cmake reads a script (`CMakeLists.txt`) with meta-information on the project and **creates a Makefile automatically**, tailored to your system configuration.
After that, you may run the `make` command, as usual.

To compile the game you should follow these steps into the root folder:

1. `cmake -G "Unix Makefiles" ..`: asks cmake to create the Makefile based on the script found in `CMakeLists.txt`.
2. `make`: compiles the codes of the game and generate an executable into `./bin` folder.

## 4. Game Interface

In order to run the game executable, you have to pass some command line arguments. The command to run the executable is as following:

`./bin/glife [<options>] <input_cfg_file>`

The options you may use are:

1. `--help`: Prints help message.
2. `--imgdir <path>`: Specify directory where output images are written to.
3. `--maxgen <num>`: Maximum number of generations to simulate.
4. `--fps <num>`: Number of generations presented per second.
5. `--blocksize <num>`: Pixel size of a cell.
6. `--bkgcolor <color>`: Color name for the background.
7. `--alivecolor <color>`: Color name for representing alive cells.
8. `--outfile <filename>`: Write the text representation of the simulation to the given filename.
9. `<input_cfg_file>`: the relative path to the input file.

Only the last one is required. Available colors are:

BLACK, BLUE, CRIMSON, DARK_GREEN, DEEP_SKY_BLUE, DODGER_BLUE, GREEN, LIGHT_BLUE, LIGHT_GREY, LIGHT_YELLOW, RED, STEEL_BLUE, WHITE and YELLOW.

## 5. Input File

Input files must follow this structure:

    <Number of rows> <Number of columns>
    <Char that represents alive>
    <Data line 1 of length equals to [Number of columns]>
    <Data line 2 of length equals to [Number of columns]>
    <Data line 3 of length equals to [Number of columns]>
    ...
    <Data line [Number of rows] of length equals to [Number of columns]>

## 6. Authorship

The authors of this project are **Carlos Eduardo Alves Sarmento** _< cealvesarmento@gmail.com >_ and **Victor Raphaell Vieira Rodrigues** _< victorvieira89@gmail.com >_.