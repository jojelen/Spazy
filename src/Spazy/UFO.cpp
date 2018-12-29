#include "UFO.h"
#include "KingPin/ResourceManager.h"
#include "HelpFunctions.h"

#include <random>

UFO::UFO(const glm::vec2 &pos, const glm::vec2 &vel, const float &width, const float &height) : _steerForce(0.1), _engineSpeed(1.5)
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
  _textureID =
  KingPin::ResourceManager::getTexture("src/Spazy/res/textures/enemyUFO.png").id;
}

UFO::~UFO() {}

void UFO::update(float deltaTime) 
{ 
  if ( glm::length(_velocity) > _maxSpeed)
  {
    _velocity = _maxSpeed *  glm::normalize(_velocity);
  }
  _position += _velocity * deltaTime; 

  steer();
}

void UFO::steer()
{
  float speedBefore = getSpeed();
  glm::vec2 forceDir = _target->getPosition() - getPosition();
  glm::normalize(forceDir);
  forceDir = glm::vec2( forceDir.y, -forceDir.x);
  applyForce(forceDir, _steerForce);
  
  if ( getSpeed()> speedBefore)
    setSpeed( speedBefore);

  else if ( getSpeed() < _engineSpeed)
    setSpeed(_engineSpeed);

}

void UFO::setTarget(Entity* target)
{ 
  _target = target;
}

void UFO::drawEffects(KingPin::SpriteBatch &spriteBatch) {}