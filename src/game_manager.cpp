#include "../include/game_manager.hpp"
#include "../include/visor.hpp";

#include <string.h>
#include <fstream>
#include <vector>

GameManager::GameManager(int argc, char *argv[])
{
  if (argc <= 2 && !strcmp(argv[1], "-h"))
  {
    visor::display_help();
  }
}
