#include "Errors.h"
#include <iostream>
#include <SDL/SDL.h>
#include <cstdlib>

namespace KingPin
{
void fatalError(std::string errorString)
{

  std::cout << "[ERROR]: " << errorString << std::endl;
  std::cin.get();
  SDL_Quit();
  exit(1);
}
} // namespace KingPin