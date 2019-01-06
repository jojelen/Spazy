#include "UFO.h"
#include "HelpFunctions.h"
#include "KingPin/ResourceManager.h"

#include <random>
#include <iostream>

UFO::UFO(const glm::vec2 &pos, const glm::vec2 &vel, const float &width,
         const float &height)
    : _steerForce(5.), _engineSpeed(1.5), _reloadTime(20.)
{
  setSize(width, height);

  _position = pos;
  _velocity = vel;

  _angle = atan(vel.y / vel.x) + M_PI;
  if (vel.x < 0)
    _angle += 1.577 + M_PI;
  _speed = getSpeed();

  // UFO specifics:
  _life = 3.0f;
  _mass = 200.0f;

  _entityType = ENEMY;
  _textureID = KingPin::ResourceManager::getTexture(
                   "src/Spazy/res/textures/enemyUFO.png")
                   .id;
}

UFO::~UFO() 
{
  std::cout << "Destroying UFO!\n";
}

void UFO::update(float deltaTime)
{
  if (glm::length(_velocity) > _maxSpeed)
  {
    _velocity = _maxSpeed * glm::normalize(_velocity);
  }
  _position += _velocity * deltaTime;

  steer();
  shoot();

  updateEffects(deltaTime);
}

void UFO::updateEffects(const float &deltaTime)
{
  // Update lasers
  for (int i = 0; i < _lasers.size(); ++i)
  {
    if (_lasers[i].update(deltaTime))
    {
      _lasers.erase(_lasers.begin() + i);
      i--;
      continue;
    }
  }
}

void UFO::shoot()
{
  if (_target != nullptr && _target->getEntityStatus() != DESTROYED)
  if (_reloadTime == 0)
  {
    _lasers.emplace_back(_position,
                         getTargetDirection(), 8.0f, 1000, GREEN);
                         _lasers.back().setImmuneTarget(this);
    _reloadTime = 150; // Reload time
  }

  if (_reloadTime > 0)
    --_reloadTime;
}

void UFO::interactWith(std::vector<Entity *> &entities)
{
  // Check if laser is colliding with entities
  for (auto &laser : _lasers)
  {
    laser.isColliding(entities); // projectileHit if it hits and destroys laser
  }
}

glm::vec2 UFO::getTargetDirection() const
{
  glm::vec2 direction = _target->getPosition() - getPosition();
  direction = glm::normalize(direction);
  return direction;
}

void UFO::steer()
{
  float speedBefore = getSpeed();
  glm::vec2 forceDir = getTargetDirection();
  forceDir = _steerForce *  glm::vec2(forceDir.y, -forceDir.x);
  applyForce(forceDir, _steerForce);

  if (getSpeed() > speedBefore)
    setSpeed(speedBefore);

  else if (getSpeed() < _engineSpeed)
    setSpeed(_engineSpeed);
}

void UFO::setTarget(Entity *target) { _target = target; }

void UFO::drawEffects(KingPin::SpriteBatch &spriteBatch)
{
  for (int i = 0; i < _lasers.size(); i++)
  {
    _lasers[i].draw(spriteBatch);
  }
}