#pragma once

#include "Entity.h"

class Asteroid : public Entity
{
public:
  Asteroid( const glm::vec2 pos);
  ~Asteroid();

  void update(float deltaTime);

  void drawEffects(KingPin::SpriteBatch &spriteBatch) override;
};
