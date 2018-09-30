#pragma once

#include "KingPin/SpriteBatch.h"
#include <glm/glm.hpp>

enum EntityType {
  ASTEROID, SPACESHIP, UNKNOWN
};

class Entity
{
public:
  Entity();
  virtual ~Entity();

  virtual void update(float deltaTime) = 0;
  void projectileHit(glm::vec2 momentum);

  void draw(KingPin::SpriteBatch &spriteBatch);
  virtual void drawEffects(KingPin::SpriteBatch &spriteBatch) = 0;

  static void setWorldSize(float width, float height);

  void setSize(float width, float height);
  void setPosition(glm::vec2 &pos);
  void setSpeed(float speed);
  void checkPosition();

  glm::vec2 getSize() const;
  glm::vec2 getPosition() const;
  glm::vec2 getDirection() const;
  glm::vec2 getVelocity() const;

  EntityType getEntityType() const;
  void spunk();
  bool getSpunkStatus() const;

  static float _worldWidth;
  static float _worldHeight;

protected:
  bool _spunked;
  float _width, _height;
  float _mass;
  float _speed, _maxSpeed;
  float _angle;

  int _textureID;

  EntityType _entityType;

  glm::vec2 _position;
  glm::vec2 _velocity;
};
