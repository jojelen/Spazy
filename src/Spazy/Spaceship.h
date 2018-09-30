#pragma once

#include "Entity.h"
#include "SDL/SDL.h"
#include "Laser.h"

#include <KingPin/InputManager.h>

struct SpaceshipControls
{
  unsigned int up, down, left, right, shoot;

  SpaceshipControls()
      : up(SDLK_w), down(SDLK_s), left(SDLK_a), right(SDLK_d), shoot(SDLK_CAPSLOCK) {}

  SpaceshipControls(unsigned int UP, unsigned int DOWN, unsigned int LEFT,
                    unsigned int RIGHT, unsigned int SHOOT)
      : up(UP), down(DOWN), left(LEFT), right(RIGHT), shoot(SHOOT) {}
};

class Spaceship : public Entity
{
public:
  Spaceship();
  ~Spaceship();

  void init(float speed, glm::vec2 pos, KingPin::InputManager &inputManager);
  void setControls(const SpaceshipControls &controls);
  void update(float deltaTime);
  void drawEffects(KingPin::SpriteBatch &spriteBatch) override;

  bool isColliding(std::vector<Entity *> &entities);
  int getScore();
private:
  std::vector<Laser> _lasers;
  int _gunReload;
  int _score;

  KingPin::InputManager *_inputManager;
  SpaceshipControls _keys;

  float _acceleration;
};
