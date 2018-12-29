#include "Asteroid.h"
#include "KingPin/ResourceManager.h"
#include "HelpFunctions.h"

#include <random>

Asteroid::Asteroid( const glm::vec2 &pos, const glm::vec2 &vel, const float &width,  const float &height)
{
  setSize( width, height);
  if ( width >= 50.0f)
    _life = 2.;

  _entityType = ASTEROID;
  _textureID =
  KingPin::ResourceManager::getTexture("src/Spazy/res/textures/asteroid.png").id;

  // Set position
  _position = pos;
  _velocity = vel;
  _mass = 1000.0f;

  _angle = atan(vel.y/vel.x) + M_PI;
  if ( vel.x < 0)
    _angle += 1.577 + M_PI;
  _speed = getSpeed();
}

Asteroid::~Asteroid() {}

void Asteroid::update(float deltaTime) 
{ 
  if ( glm::length(_velocity) > _maxSpeed)
  {
    _velocity = _maxSpeed *  glm::normalize(_velocity);
  }
  _position += _velocity * deltaTime; 

  if ( _life <= 1.0f)
    _textureID =
  KingPin::ResourceManager::getTexture("src/Spazy/res/textures/asteroidDamaged.png").id;
}

void Asteroid::drawEffects(KingPin::SpriteBatch &spriteBatch) {}