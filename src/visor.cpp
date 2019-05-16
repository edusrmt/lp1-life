#include "../include/visor.hpp"
#include <iomanip>

using namespace std;

namespace visor
{

void display_help()
{
    cout << BOLDCYAN << endl;
    cout << "Usage: " << BOLDGREEN << "glife [" << YELLOW << "<options>" << BOLDGREEN << "] " << YELLOW << "<input_cfg_file>" << endl;
    cout << RESET CYAN << "   Simulation options:" << endl
         << RESET;
    cout << "      " << MAGENTA << "--help \t\t\t" << RESET << "Print this help text." << endl;
    cout << "      " << MAGENTA << "--imgdir " << YELLOW "<path>\t\t" << RESET << "Specify directory where output images are written to." << endl;
    cout << "      " << MAGENTA << "--maxgen " << YELLOW "<num>\t\t" << RESET << "Maximum number of generations to simulate." << endl;
    cout << "      " << MAGENTA << "--fps " << YELLOW "<num>\t\t" << RESET << "Number of generations presented per second." << endl;
    cout << "      " << MAGENTA << "--blocksize " << YELLOW "<num>\t\t" << RESET << "Pixel size of a cell. Default = 5." << endl;
    cout << "      " << MAGENTA << "--bkgcolor " << YELLOW "<color>\t" << RESET << "Color name for the background. Default " << GREEN << "GREEN." << endl;
    cout << "      " << MAGENTA << "--alivecolor " << YELLOW "<color>\t" << RESET << "Color name for representing alive cells. Default " << RED << "RED." << endl;
    cout << "      " << MAGENTA << "--outfile " << YELLOW "<filename>\t" << RESET << "Write the text representation of the simulation to the given filename." << endl;
    cout << endl
         << endl;
    cout << "   " << BOLDCYAN "Available colors are:" << endl;
    cout << "      " << RESET << "BLACK BLUE CRIMSON DARK_GREEN DEEP_SKY_BLUE DODGER_BLUE" << endl;
    cout << "      "
         << "GREEN LIGHT_BLUE LIGHT_GREY LIGHT_YELLOW RED STEEL_BLUE" << endl;
    cout << "      "
         << "WHITE YELLOW" << endl;
}

void display_error(int code)
{

    std::cout << BOLDRED;

    switch (code)
    {
    case -1:
        std::cout << ">>>> Error... The algorithm doesn't exists.\n"
                  << RESET << YELLOW
                  << "     Try again with another algorithm name" << std::endl;
        break;
    case 0:
        std::cout << ">>>> Hey, you're missing arguments\n"
                  << RESET << YELLOW
                  << "     Use: --algoption <algorithm_name>\n"
                  << "     The options are:\n"
                  << "          cb" << std::endl;
        break;
    case 1:
        std::cout << ">>>> Error... The algorithm cb [cannonball] needs a <height> parameter.\n"
                  << RESET << YELLOW
                  << "     Try again with: --algoption cb <height_value>" << std::endl;
        break;
    case 2:
        std::cout << ">>>> Error... The algorithm power [power] needs a <n> and <k> parameter.\n"
                  << RESET << YELLOW
                  << "     Try again with: --algoption power <n> <k>" << std::endl;
        break;
    case 3:
        std::cout << ">>>> Error... The algorithm ds [digit_sum] needs a <number> parameter.\n"
                  << RESET << YELLOW
                  << "     Try again with: --algoption ds <number>" << std::endl;
        break;
    }

    std::cout << RESET;
}

void display_result(int alg, int result)
{
    std::cout << BOLDGREEN;

    switch (alg)
    {
    case 1:
        std::cout << ">>>> Running the [" << BOLDBLUE << "cannonball" << BOLDGREEN << "] algorithm..." << std::endl
                  << ">>>> Yaaaas! The result is: [" << RESET << result << " cannonballs" << BOLDGREEN "]" << std::endl;
        break;

    case 2:
        std::cout << ">>>> Running the [" << BOLDBLUE << "power" << BOLDGREEN << "] algorithm..." << std::endl
                  << ">>>> Yaaaas! The result is: [" << RESET << result << BOLDGREEN "]" << std::endl;
        break;

    case 3:
        std::cout << ">>>> Running the [" << BOLDBLUE << "digit_sum" << BOLDGREEN << "] algorithm..." << std::endl
                  << ">>>> Yaaaas! The result is: [" << RESET << result << BOLDGREEN "]" << std::endl;
        break;

    default:
        break;
    }

    std::cout << RESET << std::endl;
}

} // namespace visor