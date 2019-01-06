#pragma once

#include "Entity.h"

class Asteroid : public Entity {
public:
  Asteroid(const glm::vec2 &pos, const glm::vec2 &vel, const float &width,
           const float &height);
  ~Asteroid();

  void update(float deltaTime);
  void interactWith(std::vector<Entity*> &entities) override;
  void drawEffects(KingPin::SpriteBatch &spriteBatch) override;
};
