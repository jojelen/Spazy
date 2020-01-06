#pragma once

#include <KingPin/InputManager.h>
#include <KingPin/SpriteBatch.h>
#include <KingPin/Window.h>
#include <algorithm>

#include "Asteroid.h"
#include "Entity.h"
#include "Flock.h"
#include "Laser.h"
#include "PopUp.h"
#include "Spaceship.h"
#include "UFO.h"

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
  void update(const float &deltaTime);

  void draw(); // Calls effects and entities draw functions

  void addGameOver(); // Adds a GAME OVER pop up sign
  void addPlayer(int playerNr, KingPin::InputManager *inputManager,
                 KingPin::Window *window);
  void addRandomAsteroid(const float &radius);
  void addAsteroid(const glm::vec2 &pos, const glm::vec2 &vel,
                   const float &radius);
  void addUFO();
  void addExplosion(const glm::vec2 pos, float size = 100.);
  void addFlock(const int nrBirds);

  int getNumPlayers();   // Returns the number of players that are alive
  int getNumEntities();  // Returns number of non-player entities.
  int getNumAsteroids(); // Returns the number of asteroids

private:
  void loadSounds();

  void updatePlayers(const float &deltaTime);
  void updateEntities(const float &deltaTime);

  glm::vec2 getFreePosition() const; // Returns a position free of players

  void printScore() const;

  // Handles the pointers to entities, i.e. new and delete.
  // deleteEntity also erases the pointer in the respective vector.
  void addEntity(EntityType type, const glm::vec2 &pos, const glm::vec2 &vel,
                 const float &width, const float &height);
  void deleteEntity(Entity *ent);

  KingPin::SpriteBatch _entitySpriteBatch;
  KingPin::SpriteBatch _spriteBatch;
  KingPin::SpriteBatch _popBatch;

  std::vector<Entity *> _entities;
  std::vector<Asteroid *> _asteroids;

  std::vector<Bird *> _birds;
  Flock _flock;

  std::vector<UFO *> _ufos;

  std::vector<Effect *> _effects;

  std::vector<Spaceship *> _players;

  float _screenWidth, _screenHeight; // For adding content within frame
};
