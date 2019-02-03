#pragma once

#include "Entity.h"
#include "SDL/SDL.h"
#include "Laser.h"

#include <KingPin/InputManager.h>

struct SpaceshipControls
{
  unsigned int up, down, left, right, shoot;

  SpaceshipControls()
      : up(SDLK_w), down(SDLK_s), left(SDLK_a), right(SDLK_d), shoot(SDLK_SPACE) {}

  SpaceshipControls(unsigned int UP, unsigned int DOWN, unsigned int LEFT,
                    unsigned int RIGHT, unsigned int SHOOT)
      : up(UP), down(DOWN), left(LEFT), right(RIGHT), shoot(SHOOT) {}
};

class Spaceship : public Entity
{
public:
  Spaceship(const int playerNr);
  ~Spaceship();

  void init(float speed, glm::vec2 pos, KingPin::InputManager &inputManager);
  void setControls(const SpaceshipControls &controls);
  void update(float deltaTime);
  void drawEffects(KingPin::SpriteBatch &spriteBatch) override;

  void interactWith(std::vector<Entity*> &entities) override;
  // Returns true if it gets destroyed.
  bool isColliding(std::vector<Entity *> &entities); 

  void addScore(int score);
  int getScore() const;
  int getPlayerNr() const;
  float getMaxLife() const;
private:
  void shoot();
  void updateEffects( const float &deltaTime);
  void isKilling(std::vector<Entity*> &entities);

  std::vector<Laser> _lasers;
  int _gunReload;
  int _score;

  float _maxLife;
  int _playerNr;

  KingPin::InputManager *_inputManager;
  SpaceshipControls _keys;

  float _acceleration;
};
