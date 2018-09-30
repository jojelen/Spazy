#pragma once

// #include <GL/glew.h>
#include <GL/glxew.h>
#include <SDL/SDL.h>
#include <string>

namespace KingPin
{
enum WindowFlags
{
  INVISIBLE = 0x1,
  FULLSCREEN = 0x2,
  BORDERLESS = 0x4
};

class Window
{
public:
  Window();
  ~Window();

  int create(std::string windowName, int &screenWidth, int &screenHeight,
             unsigned int currentFlags);

  void swapBuffer();

  int getScreenWidth() { _screenWidth; };
  int getScreenHeight() { _screenHeight; };

private:
  int _screenWidth, _screenHeight;
  SDL_Window *_sdlWindow;
};

} // namespace KingPin