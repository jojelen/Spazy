#pragma once

#include "KingPin/SpriteBatch.h"
#include <glm/glm.hpp>

enum EntityType {
  ASTEROID, SPACESHIP, UNKNOWN, BIRD
};

enum EntityStatus {
  DESTROYED, DAMAGED, FINE
};

class Entity
{
public:
  Entity();
  virtual ~Entity();

  virtual void update(float deltaTime) = 0;

  void applyForce(glm::vec2 force, const float maxForce = -1.0f);

  void projectileHit(glm::vec2 momentum, float power);

  void draw(KingPin::SpriteBatch &spriteBatch);
  virtual void drawEffects(KingPin::SpriteBatch &spriteBatch) = 0;

  static void setWorldSize(float width, float height);

  void setSize(float width, float height);
  void setVelocity(const glm::vec2 &vel);
  void setPosition(const glm::vec2 &pos);
  void setSpeed(float speed);
  void checkPosition(); // Resets the _position to be within the frame

  glm::vec2 getSize() const;
  glm::vec2 getPosition() const;
  glm::vec2 getDirection() const;
  glm::vec2 getVelocity() const;
  float getSpeed() const;
  float getMaxSpeed() const;

  EntityType getEntityType() const;
  EntityStatus getEntityStatus() const;
  void setEntityStatus( const EntityStatus status);

  static float _worldWidth;
  static float _worldHeight;

protected:

  float _width, _height;
  float _mass;
  float _life;
  float _speed, _maxSpeed;
  float _angle;

  int _textureID;

  EntityType _entityType;
  EntityStatus _entityStatus;

  glm::vec2 _position;
  glm::vec2 _velocity;
};
