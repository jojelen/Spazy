#include "GameContent.h"
#include <iostream>

GameContent::GameContent() {}

GameContent::~GameContent() { deleteContent(); }

void GameContent::initializeSpriteBatches(float screenWidth,
                                          float screenHeight)
{
  _screenWidth = screenWidth;
  _screenHeight = screenHeight;

  // Initialize SpriteBatch
  _entitySpriteBatch.init();
  _spriteBatch.init();
  _popBatch.init();
}

int GameContent::getNumPlayers()
{
  int numPlayers = 0;
  for (auto &player : _players)
    if ( player->getEntityStatus() != DESTROYED)
      ++numPlayers;
  return numPlayers;
}

void GameContent::draw()
{

  // Draw the Entities
  _entitySpriteBatch.begin();
  for (int i = 0; i < _entities.size(); i++)
  {
    _entities[i]->draw(_entitySpriteBatch);
  }
  _entitySpriteBatch.end();
  _entitySpriteBatch.renderBatch();

  _popBatch.begin();

  // Draw the PopUps; deletes them if their lifetime is up.
  for (int i = 0; i < _effects.size(); i++)
  {
    if (_effects[i]->draw(_popBatch))
    {
      delete _effects[i];
      _effects.erase(_effects.begin() + i);
    }
  }
  _popBatch.end();
  _popBatch.renderBatch();
}

int GameContent::getNumAsteroids()
{
  return _entities.size() - _players.size();
}

void GameContent::deleteContent()
{
  std::cout << "GameContent: deleteContent():\n";

  for (unsigned int i = 0; i < _entities.size(); ++i)
    delete _entities[i];

  _players.clear();
  _entities.clear();
  _asteroids.clear();

  for (unsigned int i = 0; i < _effects.size(); ++i)
    delete _effects[i];

  _effects.clear();
}
void GameContent::update(float deltaTime)
{
  // Checks if the player is colliding with the asteroids
  for (int i = 0; i < _players.size(); ++i)
  {
    _players[i]->update(deltaTime);

    if (_players[i]->isColliding(_entities))
    {
      addExplosion(_players[i]->getPosition());
    }
  }

  // Update entities
  // Also checks for destroyed entities and adds explosions.
  for (int i = _players.size(); i < _entities.size(); ++i)
  {
    _entities[i]->update(deltaTime);
    if (_entities[i]->getEntityStatus() == DESTROYED)
    {
      addExplosion(_entities[i]->getPosition());
      delete _entities[i];
      _entities.erase(_entities.begin() + i);
    }
  }

  
}

void GameContent::addGameOver()
{
  _effects.push_back((Effect *)new PopUp(glm::vec2(0.0f, 0.0f), 1000, gameOver));
}

void GameContent::addPlayer(int playerNr, KingPin::InputManager *inputManager)
{
  // Creates a new player if that one doesn't exists, otherwise sets its status
  // to FINE.
  if (playerNr > _players.size())
  {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

    // Set position
    glm::vec2 position =
        glm::vec2(-_screenWidth / 2 + 0.01 * dist(rng) * _screenWidth,
                  -_screenHeight / 2 + 0.01 * dist(rng) * _screenHeight);

    _players.push_back(new Spaceship(playerNr));
    _players.back()->init(0.0f, position, *inputManager);
    _players.back()->setSize(50.0f, 50.0f);

    switch (playerNr)
    {
    case 1:
    {
      SpaceshipControls controls(SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDLK_SPACE);
      _players.back()->setControls(controls);
      break;
    }
    case 2:
    {
      SpaceshipControls controls(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT,
                                 SDLK_RCTRL);
      _players.back()->setControls(controls);
      break;
    }
    default:
      break;
    }
    _entities.push_back(_players.back());
  }
  else
    _players[ playerNr - 1]->setEntityStatus(FINE);
}

void GameContent::addAsteroid()
{
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

  glm::vec2 pos;
  for (;;)
  {
    // Set position
    pos = glm::vec2(-_screenWidth / 2 + 0.01 * dist(rng) * _screenWidth,
                    -_screenHeight / 2 + 0.01 * dist(rng) * _screenHeight);
    bool collidingWithPlayers = false;
    for (auto &player : _players)
    {
      float dist = glm::distance(pos, player->getPosition());
      if (dist < 100.)
        collidingWithPlayers = true;
    }
    if (!collidingWithPlayers)
      break;
  }

  _asteroids.push_back(new Asteroid(pos));
  _asteroids.back()->setSize(50.0f, 50.0f);
  _entities.push_back(_asteroids.back());
}

void GameContent::addExplosion(const glm::vec2 pos)
{
  _effects.push_back((Effect *)new Explosion(pos, 100.));
}
