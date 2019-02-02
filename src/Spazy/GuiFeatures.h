#pragma once

#include "KingPin/GuiWindow.h"
#include "Spazy.h"

class Menu : public KingPin::GuiWindow
{
  public:
  Menu(GameState *gamestate);
  ~Menu();

  void show() override;

  private:
    GameState *_gameState;
};

class FpsCounter : public KingPin::GuiWindow
{
  public:
  FpsCounter();
  ~FpsCounter();

  void show() override;
};