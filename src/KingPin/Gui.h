#pragma once

#include "GuiWindow.h"

#include <SDL/SDL.h>
#include <vector>
#include <memory>

namespace KingPin{
class Gui
{
private:
  SDL_Window* _window; 
  SDL_GLContext _glContext;

  std::vector<std::unique_ptr<GuiWindow>> _guiWindows;

public:
  Gui(/* args */);
  ~Gui();

  void init(SDL_Window* window, SDL_GLContext* glContext);

  void addWindow(std::unique_ptr<GuiWindow> &window);

  void show();
};


}