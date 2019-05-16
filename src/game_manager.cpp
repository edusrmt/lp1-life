#include "../include/game_manager.hpp"
//#include "../include/visor.hpp"
#include "../include/life.hpp"
#include "../include/canvas.hpp"
#include "../include/lodepng.h"

using namespace life;
using namespace std;

void GameManager::initialize_game(int argc, char *argv[])
{
    cout << ">>> Trying to open input file [" << argv[1] << "]... ";
    std::ifstream input;
    input.open(argv[1]);
    cout << "done!" << endl;
    
    cout << ">>> Processing data, please wait..." << endl;
    char alive;
    std::string line;

    input >> rows >> cols;
    cout << ">>> Grid size read from input file: " << rows << " rows by " << cols << " cols." << endl;
    input >> alive;
    cout << ">>> Character that represents a living cell read from input file: ’" << alive << "’" << endl;
    Life state(rows,cols);

    int row = 0;
    while (input >> line) {
        int rpt = line.size() < (size_t) cols ? line.size() : cols;

        for(int col = 0; col < rpt; col++) {
            if (line[col] == alive)                
                state.set_alive(row, col);
        }

        row++;
    }    

    /*if (argc <= 2 && !strcmp(argv[1], "-h"))
    {
        visor::display_help();
    } else if (argc <= 2) {
        input.open(argv[1]);
    }*/

    
    cout << ">>> Finished reading input data file." << endl << endl;
    cout << "****************************************************************" << endl;
    cout << "Welcome to Conway’s game of Life." << endl;
    cout << "Running a simulation on a grid of size " << rows << " by " << cols << " in which" << endl;
    cout << "each cell can either be occupied by an organism or not." << endl;
    cout << "The occupied cells change from generation to generation" << endl;
    cout << "according to the number of neighboring cells which are alive." << endl;
    cout << "****************************************************************" << endl << endl;

    log.push_back(state);
    input.close();
}

bool GameManager::stable () {
    int last = log.size() - 1;

    for (int i = 0; i < last; i++) {
        if (log[i] == log[last])
            return true;
    }    

    return false;
}

bool GameManager::game_over () {
    return stable() || log.back().extinct();
}

void GameManager::encode_png(const char* filename, const unsigned char * image, unsigned width, unsigned height)
{
    //Encode the image
    unsigned error = lodepng::encode(filename, image, width, height);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

void GameManager::evolve () {
    int neigh;
    Life state = log.back();
    Life next(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            neigh = 0;
            // Counts neighbours
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (k == 0 && l == 0)
                        continue;

                    neigh += state.check_cell(i + k, j + l);
                }
            }

            // Apply rules
            if (state.check_cell(i, j)) {
                if(neigh == 2 || neigh == 3)
                    next.set_alive(i, j);
            } else if (neigh == 3) {
                next.set_alive(i, j);
            }
        }
    }

    log.push_back(next);
    gen++;        
}

void GameManager::render () {
    cout << "Generation " << gen << ":" << endl;

    for (int i = 0; i < rows; i++) {
        cout << "[";
        for (int j = 0; j < cols; j++) {
            if (log.back().check_cell(i, j))
                cout << '*';
            else
            {
                cout << ' ';
            }            
        }

        cout << "]" << endl;
    }

    Canvas image(cols, rows, 10);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (log.back().check_cell(i, j))
                image.pixel(Point2{j, i}, Color{0,0,255});
            else
                image.pixel(Point2{j, i}, Color{255,255,255});
        }
    }

    string picpath= "./pics/gen-" + to_string(gen) + ".png";
    char picname[picpath.length() + 1];
    strcpy(picname, picpath.c_str());
    encode_png(picname, image.pixels(), image.width(), image.height());
}