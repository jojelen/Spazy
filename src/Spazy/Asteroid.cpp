#include "Asteroid.h"
#include "KingPin/ResourceManager.h"

#include <random>

Asteroid::Asteroid(float screenWidth, float screenHeight)
{
  _entityType = ASTEROID;
  _textureID =
  KingPin::ResourceManager::getTexture("src/Spazy/res/textures/asteroid.png").id;

  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

  // Set position
  _position = glm::vec2(-screenWidth / 2 + 0.01 * dist(rng) * screenWidth,
                        -screenHeight / 2 + 0.01 * dist(rng) * screenHeight);

  _mass = 10.0f;
  _spunked = false;

  _angle = dist(rng) * 0.05;
  _speed = dist(rng) * 0.05;
  _speed *= 0.1;
  _velocity = _speed * glm::vec2(std::cos(_angle), std::sin(_angle));
}

Asteroid::~Asteroid() {}

void Asteroid::update(float deltaTime) { _position += _velocity * deltaTime; }

void Asteroid::drawEffects(KingPin::SpriteBatch &spriteBatch) {}