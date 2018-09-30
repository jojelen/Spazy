#pragma once

#include "Entity.h"

#include <glm/glm.hpp>
#include <KingPin/SpriteBatch.h>

class Laser
{
public:
  Laser(glm::vec2 pos, glm::vec2 dir, float speed, int lifeTime);
  ~Laser();

  void draw(KingPin::SpriteBatch &spriteBatch);

  bool update(float deltaTime);

  bool isColliding(std::vector<Entity *> &entities);

private:
  int _lifeTime;
  int _textureID;
  float _speed;
  float _angle;
  glm::vec2 _direction;
  glm::vec2 _position;

  static KingPin::SpriteBatch _spriteBatch;
};