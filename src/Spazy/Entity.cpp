#include "Entity.h"
#include "KingPin/ResourceManager.h"

#include <iostream>

float Entity::_worldWidth = 1024.0f;
float Entity::_worldHeight = 768.0f;

Entity::Entity()
    : _width(50.0f), _height(50.f), _speed(0), _maxSpeed(4.0f), _angle(0.0f),
      _entityType(UNKNOWN),
      _position(0, 0), _velocity(0.0f, 0.0f) {}

Entity::~Entity() 
{
  std::cout << "Destroying entity!\n"; // DEBUG
}

void Entity::setWorldSize(float width, float height) {
  _worldWidth = width;
  _worldHeight = height;
}
void Entity::draw(KingPin::SpriteBatch &spriteBatch) {

  checkPosition();

  glm::vec4 destRect(_position.x, _position.y, _width, _height);
  glm::vec4 mirrorDownRect(_position.x, _position.y - _worldHeight, _width,
                           _height);
  glm::vec4 mirrorUpRect(_position.x, _position.y + _worldHeight, _width,
                         _height);
  glm::vec4 mirrorLeftRect(_position.x - _worldWidth, _position.y, _width,
                           _height);
  glm::vec4 mirrorRightRect(_position.x + _worldWidth, _position.y, _width,
                            _height);

  const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
  KingPin::Color color(255, 255, 255, 255);

  spriteBatch.draw(destRect, _angle, uvRect, _textureID, 1.0f, color);
  spriteBatch.draw(mirrorDownRect, _angle, uvRect, _textureID, 1.0f, color);
  spriteBatch.draw(mirrorUpRect, _angle, uvRect, _textureID, 1.0f, color);
  spriteBatch.draw(mirrorLeftRect, _angle, uvRect, _textureID, 1.0f, color);
  spriteBatch.draw(mirrorRightRect, _angle, uvRect, _textureID, 1.0f, color);

  drawEffects(spriteBatch);
}

void Entity::setSize(float width, float height) {
  _width = width;
  _height = height;
}

void Entity::projectileHit(glm::vec2 momentum) {
  // _textureID =
  //     KingPin::ResourceManager::getTexture("src/Spazy/res/textures/SpunkedMonkey.png").id;
  momentum /= _mass;
  _velocity += momentum;
}

void Entity::checkPosition() {
  if (_position.y > _worldHeight / 2)
    _position.y = -_worldHeight / 2;
  if (_position.y < -_worldHeight / 2)
    _position.y = _worldHeight / 2;
  if (_position.x > _worldWidth / 2)
    _position.x = -_worldWidth / 2;
  if (_position.x < -_worldWidth / 2)
    _position.x = _worldWidth / 2;
}

void Entity::setPosition(glm::vec2 &pos) { _position = pos; }
void Entity::setSpeed(float speed) { _speed = speed; }

glm::vec2 Entity::getSize() const { return glm::vec2(_width, _height); }
glm::vec2 Entity::getPosition() const { return _position; }
glm::vec2 Entity::getVelocity() const { return _velocity; }
glm::vec2 Entity::getDirection() const {
  return glm::vec2(std::cos(_angle), std::sin(_angle));
}
EntityType Entity::getEntityType() const { return _entityType; }
void Entity::spunk() { _spunked = true; }
bool Entity::getSpunkStatus() const { return _spunked; }