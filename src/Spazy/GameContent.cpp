#include "GameContent.h"
#include "Bird.h"
#include "HelpFunctions.h"

#include <iostream>
#include <string>

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
    if (player->getEntityStatus() != DESTROYED)
      ++numPlayers;
  return numPlayers;
}

void GameContent::draw()
{
  // printScore();

  // Draw the Entities
  _entitySpriteBatch.begin();
  for (int i = 0; i < _entities.size(); i++)
  {
    _entities[i]->draw(_entitySpriteBatch);
  }
  for (auto &bird : _birds)
    bird->draw( _entitySpriteBatch);

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

int GameContent::getNumAsteroids() { return _asteroids.size(); }

void GameContent::deleteContent()
{
  // std::cout << "GameContent: deleteContent():\n";

  for (unsigned int i = 0; i < _entities.size(); ++i)
    delete _entities[i];

  for (auto &bird : _birds)
    delete bird;

  _players.clear();
  _entities.clear();
  _asteroids.clear();
  _flocks.clear();
  _birds.clear();

  for (unsigned int i = 0; i < _effects.size(); ++i)
    delete _effects[i];

  _effects.clear();
}
void GameContent::update(float deltaTime)
{
  // std::cout << "GameContent::update\n";
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
      std::cout << "Adding explosion\n"; // DEBUG
      addExplosion(_entities[i]->getPosition());

      // Adds small asteroids if it was a large one
      if (_entities[i]->getSize().x >= 50.0f)
      {
        std::cout << "Adding small asteroids\n";
        static constexpr int nrAsteroids = 3;
        // Splits up the velocity of the asteroid into several ones
        std::vector<glm::vec2> velVec =
            splitVecIntoSeveral(_entities[i]->getVelocity(), nrAsteroids);
        for (int j = 0; j < nrAsteroids; ++j)
        {
          addAsteroid(_entities[i]->getPosition(), 30.0f);
          std::cout << "Setting velocity\n";
          _asteroids.back()->setVelocity(velVec[j]);
        }
        std::cout << "Done adding asteroids\n";
      }
      std::cout << "Deleting asteroid\n";
      delete _entities[i];
      _entities.erase(_entities.begin() + i);
    }
  }

  for (auto &bird : _birds)
    bird->update(deltaTime);

  for (auto &flock : _flocks)
    flock.updateFlockBehavior(deltaTime);
}

void GameContent::addFlock()
{
  static constexpr int nrBirds = 100;

  _flocks.emplace_back();

  for (int i = 0; i < nrBirds; ++i)
  {
    _birds.push_back(
        new Bird(getFreePosition(), randUnit() * 10.0f * getUnitVec()));
    _flocks.back().addBird(_birds.back());
  }

  // _flocks.back().setTarget( _players.back());
}

void GameContent::addGameOver()
{
  _effects.push_back(
      (Effect *)new PopUp(glm::vec2(0.0f, 0.0f), 1000, gameOver));
}

void GameContent::addPlayer(int playerNr, KingPin::InputManager *inputManager)
{
  // Creates a new player if that one doesn't exists, otherwise sets its status
  // to FINE.
  if (playerNr > _players.size())
  {
    // Set position
    glm::vec2 position =
        glm::vec2(-_screenWidth / 2 + randUnit() * _screenWidth,
                  -_screenHeight / 2 + randUnit() * _screenHeight);

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
    _players[playerNr - 1]->setEntityStatus(FINE);
}

void GameContent::addRandomAsteroid(const float &radius)
{
  addAsteroid(getFreePosition(), radius);
}

glm::vec2 GameContent::getFreePosition() const
{
  glm::vec2 pos;
  for (;;)
  {
    // Set position
    pos = glm::vec2(-_screenWidth / 2 + randUnit() * _screenWidth,
                    -_screenHeight / 2 + randUnit() * _screenHeight);
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
  return pos;
}

void GameContent::addAsteroid(const glm::vec2 &pos, const float &radius)
{
  std::cout << "Adding asteroid\n";
  _asteroids.push_back(new Asteroid(pos, radius));
  _entities.push_back(_asteroids.back());
}

void GameContent::addExplosion(const glm::vec2 pos)
{
  _effects.push_back((Effect *)new Explosion(pos, 100.));
}

void GameContent::printScore() const
{
  for (int i = 0; i < _players.size(); ++i)
  {
    std::cout << "Player " << (i + 1) << ": " << _players[i]->getScore() << " ";
  }
  std::cout << std::endl;
}