#pragma once

#include <SDL/SDL.h>

class Gui
{
private:
  SDL_Window* _window; 
  SDL_GLContext _glContext;
public:
  Gui(/* args */);
  ~Gui();

  void init(SDL_Window* window, SDL_GLContext* glContext);

  void show();
};


