#include "Bird.h"
#include "KingPin/ResourceManager.h"
#include "HelpFunctions.h"

#include <random>

Bird::Bird(const glm::vec2 &pos, const glm::vec2 &vel, const float &width, const float &height)
{
  setSize(width, height);

  _position = pos;
  _velocity = vel;

  _angle = atan(vel.y / vel.x) + M_PI;
  if (vel.x < 0)
    _angle += 1.577 + M_PI;
  _speed = getSpeed();

  // Bird specifics:
  _life = 2.0f;
  _mass = 5.0f;

  _entityType = BIRD;
  _textureID =
      KingPin::ResourceManager::getTexture("src/Spazy/res/textures/enemyShip.png").id;
}

Bird::~Bird()
{
}


void Bird::update(float deltaTime)
{
  if (glm::length(_velocity) > _maxSpeed)
  {
    _velocity = _maxSpeed * glm::normalize(_velocity);
  }
  _position += _velocity * deltaTime;

  _angle = std::atan(_velocity.y / _velocity.x) + M_PI;
  if (_velocity.x < 0)
    _angle += M_PI;
}

void Bird::drawEffects(KingPin::SpriteBatch &spriteBatch) {}
void Bird::interactWith(std::vector<Entity*> &entities)
{}