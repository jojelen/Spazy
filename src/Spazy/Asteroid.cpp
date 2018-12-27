#include "Asteroid.h"
#include "KingPin/ResourceManager.h"
#include "HelpFunctions.h"

#include <random>

Asteroid::Asteroid( const glm::vec2 &pos, const float &width)
{
  setSize( width, width);
  if ( width >= 50.0f)
    _life = 2.;

  _entityType = ASTEROID;
  _textureID =
  KingPin::ResourceManager::getTexture("src/Spazy/res/textures/asteroid.png").id;

  // Set position
  _position = pos;

  _mass = 1000.0f;

  _angle = randUnit() * 2.*M_PI;
  _speed = randUnit() * 5.;
  _speed *= 0.1;
  _velocity = _speed * getUnitVec();
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