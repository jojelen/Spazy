#include "Spaceship.h"
#include "KingPin/ResourceManager.h"

Spaceship::Spaceship() : _gunReload(0), _score(0)
{ _entityType = SPACESHIP; }

Spaceship::~Spaceship()  {}

void Spaceship::init(float speed, glm::vec2 pos,
                     KingPin::InputManager &inputManager)
{
  _speed = speed;
  _position = pos;
  _maxSpeed = 4.0f;
  _acceleration = 0.1f;

  // Pointer to MainGame's inputManager
  _inputManager = &inputManager;

  // Texture of spaceship
  _textureID =
      KingPin::ResourceManager::getTexture("src/Spazy/res/textures/player.png")
          .id;
}

void Spaceship::setControls(const SpaceshipControls &controls)
{
  _keys = controls;
}

void Spaceship::update(float deltaTime)
{
  // Moves the player around
  if (_inputManager->isKeyDown(_keys.right))
  {
    _angle -= 0.1f * deltaTime;
    // Change texture of spaceship
    _textureID = KingPin::ResourceManager::getTexture(
                     "src/Spazy/res/textures/playerRight.png")
                     .id;
  }
  else if (_inputManager->isKeyDown(_keys.left))
  {
    _angle += 0.1f * deltaTime;
    // Change texture of spaceship
    _textureID = KingPin::ResourceManager::getTexture(
                     "src/Spazy/res/textures/playerLeft.png")
                     .id;
  }
  else
  {
    // Default texture of spaceship
    _textureID = KingPin::ResourceManager::getTexture(
                     "src/Spazy/res/textures/player.png")
                     .id;
  }
  if (_inputManager->isKeyDown(_keys.up))
  {
    _velocity += _acceleration * glm::vec2(std::cos(_angle), std::sin(_angle)) *
                 deltaTime;
    // Change texture of spaceship
    _textureID = KingPin::ResourceManager::getTexture(
                     "src/Spazy/res/textures/playerForward.png")
                     .id;
  }
  else if (_inputManager->isKeyDown(_keys.down))
  {
    //_velocity -= _acceleration * glm::vec2(std::cos(_angle),
    // std::sin(_angle));
  }
  if (glm::length(_velocity) > 4.0f)
    _velocity = 4.0f * glm::normalize(_velocity); // Speed Limiter

  _position += _velocity * deltaTime;

  if (_inputManager->isKeyDown(_keys.shoot))
  {
    if (_gunReload == 0)
    {
      _lasers.emplace_back(_position + 0.5f * (getSize()).y * getDirection(),
                           getDirection(), 10.0f, 1000);
      _gunReload = 10;
    }
  }

  if (_gunReload > 0)
    _gunReload--;

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

bool Spaceship::isColliding(std::vector<Entity *> &entities)
{
  // Check laser collisions
  for (int i = 0; i < _lasers.size(); i++)
  {
    if (_lasers[i].isColliding(entities))
    {
      // _popUps.push_back(new PopUp(_position, 100, plusOne));
      _score++;
      // printScore();
      // addAsteroid();
    }
  }

  // Check if ship is colliding
  for (int i = 1; i < entities.size(); i++)
  {
    if (entities[i]->getEntityType() != SPACESHIP)
    {
      glm::vec2 entitySize = entities[i]->getSize();
      float radie = entitySize.x > entitySize.y ? entitySize.x : entitySize.y;
      glm::vec2 temp = entities[i]->getPosition();
      float distance = glm::distance(entities[i]->getPosition(), _position);

      if (distance < radie)
      {
        return true;
      }
    }
  }
  return false;
}

void Spaceship::drawEffects(KingPin::SpriteBatch &spriteBatch)
{
  for (int i = 0; i < _lasers.size(); i++)
  {
    _lasers[i].draw(spriteBatch);
  }
}

int Spaceship::getScore() { return _score; }