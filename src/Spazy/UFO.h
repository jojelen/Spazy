#pragma once

#include "Entity.h"

class UFO : public Entity
{
public:
  UFO( const glm::vec2 &pos, const glm::vec2 &vel, const float &width, const float &height);
  ~UFO();

  void update(float deltaTime);

  void setTarget(Entity* target);

  void drawEffects(KingPin::SpriteBatch &spriteBatch) override;
private:

  void steer();

  float _steerForce;
  float _engineSpeed;

  Entity* _target;
};
