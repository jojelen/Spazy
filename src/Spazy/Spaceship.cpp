#include "Spaceship.h"
#include "KingPin/ResourceManager.h"

Spaceship::Spaceship(const int playerNr)
    : _gunReload(0), _score(0), _playerNr(playerNr)
{
  _entityType = SPACESHIP;
}

Spaceship::~Spaceship() {}

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
  if (_playerNr == 1)
  {
    _textureID = KingPin::ResourceManager::getTexture(
                     "src/Spazy/res/textures/player.png")
                     .id;
  }
  else
  {
    _textureID = KingPin::ResourceManager::getTexture(
                     "src/Spazy/res/textures/player2.png")
                     .id;
  }
}

void Spaceship::setControls(const SpaceshipControls &controls)
{
  _keys = controls;
}

void Spaceship::update(float deltaTime)
{
  static const int normalText[2] = {KingPin::ResourceManager::getTexture(
                         "src/Spazy/res/textures/player.png")
                         .id,
                         KingPin::ResourceManager::getTexture(
                         "src/Spazy/res/textures/player2.png")
                         .id};
  static const int forwardText[2] = {
                         KingPin::ResourceManager::getTexture(
                         "src/Spazy/res/textures/playerForward.png")
                         .id,
                         KingPin::ResourceManager::getTexture(
                         "src/Spazy/res/textures/playerForward2.png")
                         .id};

  if (_entityStatus != DESTROYED)
  {
    // Moves the player around
    if (_inputManager->isKeyDown(_keys.right))
    {
      _angle -= 0.1f * deltaTime;
    }
    else if (_inputManager->isKeyDown(_keys.left))
    {
      _angle += 0.1f * deltaTime;
    }
    else
    {
      _textureID = normalText[ _playerNr -1 ]; // Default texture of spaceship
    }
    if (_inputManager->isKeyDown(_keys.up))
    {
      _velocity += _acceleration *
                   glm::vec2(std::cos(_angle), std::sin(_angle)) * deltaTime;
      _textureID = forwardText[ _playerNr -1 ]; // Change texture of spaceship
    }
    else if (_inputManager->isKeyDown(_keys.down))
    {
      // No brakes implemented
    }
    if (glm::length(_velocity) > 4.0f)
      _velocity = 4.0f * glm::normalize(_velocity); // Speed Limiter

    _position += _velocity * deltaTime;

    if (_inputManager->isKeyDown(_keys.shoot))
    {
      if (_gunReload == 0)
      {
        _lasers.emplace_back(_position + 0.5f * (getSize()).y * getDirection(),
                             getDirection(), 15.0f, 1000,
                             (COLOR)(_playerNr - 1));
        _gunReload = 20; // Reload time
      }
    }

    if (_gunReload > 0)
      _gunReload--;
  }
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

void Spaceship::isKilling(std::vector<Entity *> &entities)
{

  // Check if laser is colliding with entities
  for (auto &laser : _lasers)
  {
    if (laser.isColliding(entities)) // projectileHit if it hits and destroys laser
    {
      ++_score;
    }
  }
}

bool Spaceship::isColliding(std::vector<Entity *> &entities)
{
  if (_entityStatus != DESTROYED)
  {
    // Check if ship is colliding
    for (int i = 1; i < entities.size(); i++)
    {
      if (entities[i]->getEntityType() == ASTEROID)
      {
        glm::vec2 entitySize = entities[i]->getSize();
        float radie = entitySize.x > entitySize.y ? entitySize.x : entitySize.y;
        glm::vec2 temp = entities[i]->getPosition();
        float distance = glm::distance(entities[i]->getPosition(), _position);

        if (distance < radie)
        {
          _entityStatus = DESTROYED;
          return true;
        }
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