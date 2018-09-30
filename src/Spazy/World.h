#pragma once

#include "KingPin/SpriteBatch.h"
class World
{
public:
  World();
  ~World();

  void init();

  void draw();

private:
  int _textureID;

  KingPin::SpriteBatch _spriteBatch;
};
