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
    state = Life(rows,cols);

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

    input.close();
}

bool GameManager::game_over () {
    return state.extinct();
}

void GameManager::encode_png(const char* filename, const unsigned char * image, unsigned width, unsigned height)
{
    //Encode the image
    unsigned error = lodepng::encode(filename, image, width, height);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

bool GameManager::save_ppm3( const unsigned char * data, size_t w, size_t h, size_t d,  const std::string & file_name_ )
{
    std::ofstream ofs_file( file_name_, std::ios::out  );
    if ( not ofs_file.is_open() )
        return false;

    ofs_file << "P3\n"
        << w << " " << h << "\n"
        << "255\n";

    size_t i{0};
    while ( i < (w*h*d) )
    {
        // depth traversal, usually 3.
        for( auto id{0u} ; id < 3 ; id++ )
            ofs_file << (int) *(data + i++ ) << " ";
        ofs_file << std::endl;
        i++; // to skip alpha channel.
    }

    // Did it not fail?
    auto result = not ofs_file.fail();

    ofs_file.close();

    return result;
}

void GameManager::evolve () {
    
}

void GameManager::render () {
    cout << "Generation " << gen << ":" << endl;

    for (int i = 0; i < rows; i++) {
        cout << "[";
        for (int j = 0; j < cols; j++) {
            if (state.grid[i][j] == true)
                cout << '*';
            else if (state.grid[i][j] == false)
            {
                cout << ' ';
            }            
        }

        std::cout << "]" << std::endl;
    }

    Canvas image(cols, rows, 10);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (state.grid[i][j])
                image.pixel(Point2{j, i}, Color{255,255,255});
            else
                image.pixel(Point2{j, i}, Color{0,0,0});
        }
    }

    encode_png("test.png", image.pixels(), image.width(), image.height() );
    save_ppm3( image.pixels(), image.width(), image.height(), 4, "test.ppm");
}