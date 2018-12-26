#pragma once

#include "Entity.h"

class Bird : public Entity
{
  public:
  Bird(const glm::vec2 &pos, const glm::vec2 &vel);
  ~Bird();

  void update(float deltaTime) override;
  void drawEffects(KingPin::SpriteBatch &spriteBatch) override;
  private:


};