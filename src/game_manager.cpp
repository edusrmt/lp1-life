#include "../include/game_manager.hpp"

using namespace life;
using namespace std;

Color GameManager::stringToColor (char *string) {
    if(!strcmp(string, "WHITE")) {
        return WHITE;
    } else if (!strcmp(string, "DARK_GREEN")) {
        return DARK_GREEN;
    } else if (!strcmp(string, "GREEN")) {
        return GREEN;
    } else if (!strcmp(string, "RED")) {
        return RED;
    } else if (!strcmp(string, "CRIMSON")) {
        return CRIMSON;
    } else if (!strcmp(string, "BLUE")) {
        return BLUE;
    } else if (!strcmp(string, "LIGHT_BLUE")) {
        return LIGHT_BLUE;
    } else if (!strcmp(string, "LIGHT_GREY")) {
        return LIGHT_GREY;
    } else if (!strcmp(string, "DEEP_SKY_BLUE")) {
        return DEEP_SKY_BLUE;
    } else if (!strcmp(string, "DODGER_BLUE")) {
        return DODGER_BLUE;
    } else if (!strcmp(string, "STEEL_BLUE")) {
        return STEEL_BLUE;
    } else if (!strcmp(string, "YELLOW")) {
        return YELLOW;
    } else if (!strcmp(string, "LIGHT_YELLOW")) {
        return LIGHT_YELLOW;
    } else if (!strcmp(string, "BLACK")) {
        return BLACK;
    } else {
        return BLACK;
    }
}

bool GameManager::initialize_game(int argc, char *argv[])
{
    if (argc == 1) {
        cout << ">>> No arguments received!" << endl << endl;
        print_help();
        return 0;
    } else if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
        print_help();
        return 0;
    } else {
        for (int i = 1; i < argc; i++) {
            if (!strcmp(argv[i], "--imgdir")) {
                settings.imgdir = argv[++i];
            } else if (!strcmp(argv[i], "--maxgen")) {
                settings.maxgen = atoi(argv[++i]);
            } else if (!strcmp(argv[i], "--fps")) {
                settings.fps = atoi(argv[++i]);
            } else if (!strcmp(argv[i], "--blocksize")) {
                settings.blocksize = atoi(argv[++i]);
            } else if (!strcmp(argv[i], "--bkgcolor")) {
                settings.bkgcolor = stringToColor(argv[++i]);
            } else if (!strcmp(argv[i], "--alivecolor")) {
                settings.alivecolor = stringToColor(argv[++i]);
            } else if (!strcmp(argv[i], "--outfile")) {
                settings.outfile = argv[++i] ;
            } else {
                settings.input_cfg_file = argv[i];
            }
        }
    }

    if(settings.input_cfg_file == nullptr) {
        cout << ">>> No input file given!" << endl;
        return false;
    }

    cout << ">>> Trying to open input file [" << settings.input_cfg_file << "]... ";
    std::ifstream input;
    input.open(settings.input_cfg_file);
    
    if (input.is_open())
        cout << "done!" << endl;
    else {
        cout << "fail!" << endl;
        return 0;
    }    
    
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

    std::ofstream output;
    output.open(settings.outfile, std::ofstream::trunc);
    output.close();   
    
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

    return 1;
}

bool GameManager::stable () {
    int last = log.size() - 1;

    for (int i = 0; i < last; i++) {
        if (log[i] == log[last]) {
            cout << ">>> Stability found! Generation " << gen << " would be equal to generation " << i << "!" << endl;
            return true;
        }
    }    

    return false;
}

bool GameManager::game_over () {
    if (stable() || log.back().extinct()) {
        if(log.back().extinct())
            cout << ">>> Population is extinct in generation " << gen << "!" << endl;

        return true;
    } else if (settings.maxgen != -1 && gen > settings.maxgen) {
        cout << ">>> Reached max generation amount of " << settings.maxgen << "!" << endl;
        return true;
    }
    
    return false;
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

void GameManager::wait () {
    if(settings.fps != -1)        
        this_thread::sleep_for(chrono::milliseconds((int) ((1.0 / settings.fps) * 1000)));
}

void GameManager::render () {
    if (settings.imgdir != nullptr) {
        Canvas image(cols, rows, settings.blocksize);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (log.back().check_cell(i, j))
                    image.pixel(Point2{j, i}, settings.alivecolor);
                else
                    image.pixel(Point2{j, i}, settings.bkgcolor);
            }
        }

        string inputdir(settings.imgdir);
        if(inputdir.back() != '/')
            inputdir.append("/");        

        string picpath= inputdir + "gen-" + to_string(gen) + ".png";
        cout << picpath << endl;
        char picname[picpath.length() + 1];
        strcpy(picname, picpath.c_str());
        encode_png(picname, image.pixels(), image.width(), image.height());
    }

    if (settings.outfile != nullptr) {
        std::ofstream output;
        output.open(settings.outfile, std::ofstream::app);

        output << "Generation " << gen << ":" << endl;    
        for (int i = 0; i < rows; i++) {
            output << "[";
            for (int j = 0; j < cols; j++) {
                if (log.back().check_cell(i, j))
                    output << '*';
                else
                {
                    output << ' ';
                }            
            }

            output << "]" << endl;
        }

        output.close();
    }

    if (settings.imgdir == nullptr && settings.outfile == nullptr) {
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

        wait();
    }       
}

void GameManager::print_help () {
    cout << "Usage: glife [<options>] <input_cfg_file>" << endl << endl;
    cout << "  Simulation options:" << endl;
    cout << "    --help\t\t\tPrint this help text." << endl;
    cout << "    --imgdir <path>\t\tSpecify directory where output images are written to." << endl;
    cout << "    --maxgen <num>\t\tMaximum number of generations to simulate." << endl;
    cout << "    --fps <num>\t\t\tNumber of generations presented per second." << endl;
    cout << "    --blocksize <num>\t\tPixel size of a cell. Default = 5." << endl;
    cout << "    --bkgcolor <color>\t\tColor name for the background. Default GREEN." << endl;
    cout << "    --alivecolor <color>\tColor name for representing alive cells. Default RED." << endl;
    cout << "    --outfile <filename>\tWrite the text representation of the\n\t\t\t\tsimulation to the given filename." << endl << endl;
    cout << "  Available colors are:" << endl;
    cout << "    BLACK BLUE CRIMSON DARK_GREEN DEEP_SKY_BLUE DODGER_BLUE" << endl;
    cout << "    GREEN LIGHT_BLUE LIGHT_GREY LIGHT_YELLOW RED STEEL_BLUE" << endl;
    cout << "    WHITE YELLOW" << endl;
}