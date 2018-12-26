#pragma once

#include "Entity.h"

#include <KingPin/SpriteBatch.h>
#include <glm/glm.hpp>

enum COLOR
{
  RED,
  GREEN
};

class Laser
{
public:
  Laser(const glm::vec2 &pos, const glm::vec2 &dir, const float &speed,
        const int &lifeTime, const COLOR &color);
  ~Laser();

  void draw(KingPin::SpriteBatch &spriteBatch);

  bool update(float deltaTime);

  bool isColliding(std::vector<Entity *> &entities);

  // Sets the color of the laser and changes _textureID if necessary
  void setColor(const COLOR color);

private:
  int _lifeTime;
  int _textureID;
  float _speed;
  float _angle;
  glm::vec2 _direction;
  glm::vec2 _position;

  COLOR _color;

  static KingPin::SpriteBatch _spriteBatch;
};