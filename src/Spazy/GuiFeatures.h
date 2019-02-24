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

class LevelCounter : public KingPin::GuiWindow
{
  public:
  LevelCounter(int* level);
  ~LevelCounter();

  void show() override;

  private:
  int *_level;
};

class FpsCounter : public KingPin::GuiWindow
{
  public:
  FpsCounter();
  ~FpsCounter();

  void show() override;
};

class PlayerInfo : public KingPin::GuiWindow
{
  public:
  PlayerInfo(Spaceship* player);
  ~PlayerInfo();

  void show() override;

  private:
    Spaceship* _player;
};