#pragma once

#include <KingPin/InputManager.h>
#include <KingPin/SpriteBatch.h>

#include <algorithm>

#include "Asteroid.h"
#include "Entity.h"
#include "Laser.h"
#include "PopUp.h"
#include "Spaceship.h"
#include "Flock.h"

class GameContent {
public:
  GameContent();
  ~GameContent();

  void deleteContent();

  void initializeSpriteBatches(float screenWidth, float screenHeight);

  // @brief: Updates the game content:
  //  1.) Updates the players and subsequently their lasers. Checks for
  //      collisions with other entities.
  //  2.) Updates other entities: checks DESTROYED status and deletes the
  //      entity and adds an explosion if so.
  void update(float deltaTime);

  void draw(); // Calls effects and entities draw functions

  void addGameOver(); // Adds a GAME OVER pop up sign

  void addPlayer(int playerNr, KingPin::InputManager *inputManager);

  void addRandomAsteroid(const float &radius);
  void addAsteroid(const glm::vec2 &pos, const float &radius);

  void addExplosion(const glm::vec2 pos);

  void addFlock(const int nrBirds);

  int getNumPlayers();   // Returns the number of players that are alive
  int getNumAsteroids(); // Returns the number of asteroids

private:
  glm::vec2 getFreePosition() const; // Returns a position free of players
  void printScore() const;

  KingPin::SpriteBatch _entitySpriteBatch;
  KingPin::SpriteBatch _spriteBatch;
  KingPin::SpriteBatch _popBatch;

  std::vector<Entity *> _entities;
  std::vector<Asteroid *> _asteroids;

  std::vector<Bird*> _birds;
  std::vector<Flock> _flocks;

  std::vector<Effect *> _effects;

  std::vector<Spaceship *> _players;

  // For adding content within frame
  float _screenWidth, _screenHeight;
};
