#pragma once

#include "Entity.h"

class Asteroid : public Entity
{
public:
  Asteroid(float screenWidth, float screenHeight);
  ~Asteroid();

  void update(float deltaTime);

  void drawEffects(KingPin::SpriteBatch &spriteBatch) override;
};
