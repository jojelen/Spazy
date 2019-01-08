#include "GameContent.h"
#include "Bird.h"
#include "HelpFunctions.h"

#include <iostream>
#include <string>

GameContent::GameContent() {}

GameContent::~GameContent() { deleteContent(); }

void GameContent::initializeSpriteBatches(float screenWidth,
                                          float screenHeight) {
  _screenWidth = screenWidth;
  _screenHeight = screenHeight;

  // Initialize SpriteBatch
  _entitySpriteBatch.init();
  _spriteBatch.init();
  _popBatch.init();
}

int GameContent::getNumPlayers() {
  int numPlayers = 0;
  for (auto &player : _players)
    if (player->getEntityStatus() != DESTROYED)
      ++numPlayers;
  return numPlayers;
}

void GameContent::draw() {
  // printScore();

  // Draw the Entities
  _entitySpriteBatch.begin();
  for (int i = 0; i < _entities.size(); i++) {
    _entities[i]->draw(_entitySpriteBatch);
  }
  for (auto &bird : _birds)
    bird->draw(_entitySpriteBatch);

  _entitySpriteBatch.end();
  _entitySpriteBatch.renderBatch();

  _popBatch.begin();

  // Draw the PopUps; deletes them if their lifetime is up.
  for (int i = 0; i < _effects.size(); i++) {
    if (_effects[i]->draw(_popBatch)) {
      delete _effects[i];
      _effects.erase(_effects.begin() + i);
    }
  }
  _popBatch.end();
  _popBatch.renderBatch();
}

int GameContent::getNumEntities() {
  int ents = 0;
  ents += _asteroids.size();
  ents += _ufos.size();
  ents += _birds.size();
  return ents;
}

int GameContent::getNumAsteroids() { return _asteroids.size(); }

void GameContent::deleteContent() {
  std::cout << "GameContent: deleteContent():\n";

  for (unsigned int i = 0; i < _entities.size(); ++i)
    delete _entities[i];

  for (auto &bird : _birds) {
    _flock.deleteBird(bird);
  }

  _players.clear();
  _entities.clear();
  _asteroids.clear();
  _birds.clear();

  for (unsigned int i = 0; i < _effects.size(); ++i)
    delete _effects[i];

  _effects.clear();

  std::cout << "Finished deleting content!\n";
}

void GameContent::addEntity(EntityType type, const glm::vec2 &pos,
                            const glm::vec2 &vel, const float &width,
                            const float &height) {
  switch (type) {
  case ASTEROID: {
    _asteroids.push_back(new Asteroid(pos, vel, width, height));
    _entities.push_back(_asteroids.back());
    break;
  }
  case BIRD: {
    _birds.push_back(new Bird(pos, vel, width, height));
    _entities.push_back(_birds.back());
    break;
  }
  case ENEMY: {
    _ufos.push_back(new UFO(pos, vel, width, height));
    _entities.push_back(_ufos.back());
    break;
  }
  default:
    break;
  }
}

void GameContent::deleteEntity(Entity *ent) {
  EntityType type = ent->getEntityType();

  delete ent;

  for (int i = 0; i < _entities.size(); ++i) {
    if (_entities[i] == ent) {
      std::cout << "Erasing entity from _entities!\n";
      _entities.erase(_entities.begin() + i);
      break;
    }
  }

  switch (type) {
  case ASTEROID: {
    for (int i = 0; i < _asteroids.size(); ++i) {
      if (_asteroids[i] == ent) {
        _asteroids.erase(_asteroids.begin() + i);
        break;
      }
    }
    break;
  }
  case BIRD: {
    for (int i = 0; i < _birds.size(); ++i) {
      if (_birds[i] == ent) {
        _birds.erase(_birds.begin() + i);
        break;
      }
    }
    _flock.deleteBird((Bird *)ent);
    break;
  }
  case ENEMY: {
    for (int i = 0; i < _ufos.size(); ++i) {
      if (_ufos[i] == ent) {
        _ufos.erase(_ufos.begin() + i);
        break;
      }
    }
    break;
  }
  default:
    break;
  }
}

void GameContent::update(const float &deltaTime) {
  updatePlayers(deltaTime);
  updateEntities(deltaTime);
}

void GameContent::updatePlayers(const float &deltaTime) {
  for (int i = 0; i < _players.size(); ++i) {
    _players[i]->update(deltaTime);
    _players[i]->interactWith(_entities);

    // Checks if the player is colliding with the asteroids
    if (_players[i]->isColliding(_entities)) {
      addExplosion(_players[i]->getPosition());
      _players[i]->setVelocity(glm::vec2(0., 0.));
    }
  }
}

void GameContent::updateEntities(const float &deltaTime) {
  // Also checks for destroyed entities and adds explosions.
  for (int i = _players.size(); i < _entities.size(); ++i) {
    if (_entities[i]->getEntityStatus() == DESTROYED) {
      std::cout << "Adding explosion\n"; // DEBUG
      addExplosion(_entities[i]->getPosition());

      // Adds small asteroids if it was a large one
      if (_entities[i]->getEntityType() == ASTEROID &&
          _entities[i]->getSize().x >= 50.0f) {
        std::cout << "Adding small asteroids\n";
        static constexpr int nrAsteroids = 3;

        // Splits up the velocity of the asteroid into several ones
        std::vector<glm::vec2> velVec =
            splitVecIntoSeveral(_entities[i]->getVelocity(), nrAsteroids);
        for (int j = 0; j < nrAsteroids; ++j) {
          addAsteroid(_entities[i]->getPosition(), velVec[j], 30.0f);
        }
      }

      deleteEntity(_entities[i]);
    } else {
      _entities[i]->interactWith(_entities);
      _entities[i]->update(deltaTime);
    }
  }

  _flock.updateFlockBehavior(deltaTime);
}

void GameContent::addFlock(const int nrBirds) {
  constexpr float BIRD_WIDTH = 30.;
  for (int i = 0; i < nrBirds; ++i) {
    addEntity(BIRD, getFreePosition(), randUnit() * 10.0f * getUnitVec(),
              BIRD_WIDTH, BIRD_WIDTH);
    _flock.addBird(_birds.back());
  }
}

void GameContent::addGameOver() {
  _effects.push_back(
      (Effect *)new PopUp(glm::vec2(0.0f, 0.0f), 1000, gameOver));
}

void GameContent::addPlayer(int playerNr, KingPin::InputManager *inputManager) {
  // Creates a new player if that one doesn't exists, otherwise sets its status
  // to FINE.
  if (playerNr > _players.size()) {
    // Set position
    glm::vec2 position =
        glm::vec2(-_screenWidth / 2 + randUnit() * _screenWidth,
                  -_screenHeight / 2 + randUnit() * _screenHeight);

    _players.push_back(new Spaceship(playerNr));
    _players.back()->init(0.0f, position, *inputManager);
    _players.back()->setSize(50.0f, 50.0f);

    switch (playerNr) {
    case 1: {
      SpaceshipControls controls(SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDLK_SPACE);
      _players.back()->setControls(controls);
      break;
    }
    case 2: {
      SpaceshipControls controls(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT,
                                 SDLK_RCTRL);
      _players.back()->setControls(controls);
      break;
    }
    default:
      break;
    }
    _entities.push_back(_players.back());
  } else {
    _players[playerNr - 1]->setEntityStatus(FINE);
    if (_players[playerNr - 1]->getSpeed() > 0.1)
      _players[playerNr - 1]->setSpeed(0.f);
  }
}

void GameContent::addRandomAsteroid(const float &radius) {
  addEntity(ASTEROID, getFreePosition(), getUnitVec(), radius, radius);
}

glm::vec2 GameContent::getFreePosition() const {
  glm::vec2 pos;
  for (;;) {
    // Set position
    pos = glm::vec2(-_screenWidth / 2 + randUnit() * _screenWidth,
                    -_screenHeight / 2 + randUnit() * _screenHeight);
    bool collidingWithPlayers = false;
    for (auto &player : _players) {
      float dist = glm::distance(pos, player->getPosition());
      if (dist < 100.)
        collidingWithPlayers = true;
    }
    if (!collidingWithPlayers)
      break;
  }
  return pos;
}

void GameContent::addAsteroid(const glm::vec2 &pos, const glm::vec2 &vel,
                              const float &radius) {
  addEntity(ASTEROID, pos, vel, radius, radius);
}

void GameContent::addUFO() {
  glm::vec2 pos = getFreePosition();
  glm::vec2 vel = getUnitVec();
  addEntity(ENEMY, pos, vel, 50., 50.);

  for (auto &player : _players) {
    if (player != nullptr)
      _ufos.back()->setTarget((Entity *)player);
  }
}

void GameContent::addExplosion(const glm::vec2 pos) {
  _effects.push_back((Effect *)new Explosion(pos, 100.));
}

void GameContent::printScore() const {
  for (int i = 0; i < _players.size(); ++i) {
    std::cout << "Player " << (i + 1) << ": " << _players[i]->getScore() << " ";
  }
  std::cout << std::endl;
}