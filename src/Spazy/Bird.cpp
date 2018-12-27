#include "Bird.h"
#include "KingPin/ResourceManager.h"
#include "HelpFunctions.h"

#include <random>

Bird::Bird(const glm::vec2 &pos, const glm::vec2 &vel)
{

  _entityType = BIRD;
  _textureID =
  KingPin::ResourceManager::getTexture("src/Spazy/res/textures/enemyShip.png").id;

  setSize(30.,30.);

  // Set position
  _position = pos;
  _velocity = vel;

  _life = 5.0f;
  _mass = 5.0f;
  // _maxSpeed = 3.0f;
  _angle = randUnit() * 2. * M_PI;
}

Bird::~Bird()
{

}

void Bird::update(float deltaTime)
{
  if ( glm::length(_velocity) > _maxSpeed)
  {
    _velocity = _maxSpeed *  glm::normalize(_velocity);
  }
  _position += _velocity * deltaTime; 

  _angle = std::atan( _velocity.y / _velocity.x ) + M_PI;
  if ( _velocity.x < 0)
    _angle += M_PI;

  
}

void Bird::drawEffects(KingPin::SpriteBatch &spriteBatch) {}