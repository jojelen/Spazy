#pragma once

#include "Entity.h"
#include "Laser.h"

class UFO : public Entity
{
public:
  UFO( const glm::vec2 &pos, const glm::vec2 &vel, const float &width, const float &height);
  ~UFO();

  void update(float deltaTime);
  void interactWith(std::vector<Entity*> &entities) override;

  void setTarget(Entity* target);

  void drawEffects(KingPin::SpriteBatch &spriteBatch) override;
private:

  void steer();
  void updateEffects(const float &deltaTime);
  void shoot();
  glm::vec2 getTargetDirection() const;

  float _steerForce;
  float _engineSpeed;

  int _reloadTime;
  std::vector<Laser> _lasers;


  std::vector<Entity*> _targets;
};
