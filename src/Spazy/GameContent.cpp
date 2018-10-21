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
int GameContent::getNumPlayers() { return _players.size(); }
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

  // Draw the PopUps
  for (int i = 0; i < _popUps.size(); i++)
  {
    if (_popUps[i]->draw(_popBatch))
    {
      _popUps.erase(_popUps.begin() + i);
      // i--;
    }
  }
  _popBatch.end();
  _popBatch.renderBatch();
}

int GameContent::getNumAsteroids() 
{ 
  return _entities.size()-_players.size(); }
void GameContent::deleteContent()
{

  for (unsigned int i = 0; i < _entities.size(); ++i)
    delete _entities[i];

  _entities.clear();
  _asteroids.clear();

  for (unsigned int i = 0; i < _popUps.size(); ++i)
    delete _popUps[i];

  _popUps.clear();
}
void GameContent::update(float deltaTime)
{

  // Update entities
  for (auto &entity : _entities)
    entity->update(deltaTime);

  // Checks if the player is colliding with the asteroids
  for (int i = 0; i < _players.size(); ++i)
  {
    if (_players[i]->isColliding(_entities))
    {
      std::cout << "delete _players[i]\n"; // DEBUG
      delete _players[i];
      _entities.erase(_entities.begin() + i);
      _players.erase(_players.begin() + i);
      std::cout << "have erased player\n"; // DEBUG
    }
  }
}

void GameContent::addGameOver()
{

  _popUps.push_back(new PopUp(glm::vec2(0.0f, 0.0f), 1000, gameOver));
}

void GameContent::addPlayer(int controls, KingPin::InputManager *inputManager)
{
  std::mt19937 rng;
  rng.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> dist(0, 100);

  // Set position
  glm::vec2 position =
      glm::vec2(-_screenWidth / 2 + 0.01 * dist(rng) * _screenWidth,
                -_screenHeight / 2 + 0.01 * dist(rng) * _screenHeight);

  _players.push_back(new Spaceship());
  _players.back()->init(0.0f, position, *inputManager);
  _players.back()->setSize(50.0f, 50.0f);
  switch (controls)
  {
  case 0:
    break;
  case 1:
    SpaceshipControls controls(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT,
                               SDLK_RCTRL);
    _players.back()->setControls(controls);
    break;
  }
  _entities.push_back(_players.back());
}

void GameContent::addAsteroid()
{
  _asteroids.push_back(new Asteroid(_screenWidth, _screenHeight));
  _asteroids.back()->setSize(50.0f, 50.0f);
  _entities.push_back(_asteroids.back());
}
