#include <SDL/SDL.h>

namespace KingPin
{

int init()
{

  SDL_Init(SDL_INIT_EVERYTHING);

  //Doublebuffering prevents flickering
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  return 0;
}
} // namespace KingPin
