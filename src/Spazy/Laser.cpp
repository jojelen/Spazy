#include "Laser.h"
#include "KingPin/ResourceManager.h"
#include "KingPin/SpriteBatch.h"

Laser::Laser(const glm::vec2 &pos, const glm::vec2 &dir, const float &speed,
             const int &lifeTime, const COLOR &color)
    : _lifeTime(lifeTime), _position(pos), _direction(dir),  _speed(speed), _mass(20.f), _immuneTarget(nullptr),
      _color(color)
{
  _angle = atan(dir.y / dir.x) + 1.577;
  if (dir.x < 0)
    _angle += M_PI;

  switch (_color)
  {
  case RED:
    _textureID = KingPin::ResourceManager::getTexture(
                     "src/Spazy/res/textures/laserRed.png")
                     .id;
    break;
  case GREEN:
    _textureID = KingPin::ResourceManager::getTexture(
                     "src/Spazy/res/textures/laserGreen.png")
                     .id;
    break;
  default:
    break;
  }
}

Laser::~Laser() {}

void Laser::setImmuneTarget(Entity* ent)
{
  _immuneTarget = ent;
}

void Laser::draw(KingPin::SpriteBatch &spriteBatch)
{
  glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
  KingPin::Color color(255, 255, 255, 255);

  static const float width = 5.0f;
  static const float height = 25.0f;
  glm::vec4 posAndSize = glm::vec4(_position.x, _position.y, width, height);
  spriteBatch.draw(posAndSize, _angle, uv, _textureID, 0.0f, color);
}

bool Laser::update(float deltaTime)
{
  _position += _direction * _speed * deltaTime;
  if (_lifeTime == 0)
  {
    return true;
  }
  _lifeTime--;
  return false;
}

void Laser::setColor(const COLOR color)
{
  if (color != _color)
  {
    _color = color;
    switch (color)
    {
    case RED:
      _textureID = KingPin::ResourceManager::getTexture(
                       "src/Spazy/res/textures/laserRed.png")
                       .id;
      break;
    case GREEN:
      _textureID = KingPin::ResourceManager::getTexture(
                       "src/Spazy/res/textures/laserGreen.png")
                       .id;
      break;
    default:
      break;
    }
  }
}

bool Laser::isColliding(std::vector<Entity *> &entities)
{
  glm::vec2 momentum = _mass * _direction * _speed;

  for (int i = 0; i < entities.size(); i++)
  {
    if (entities[i] != _immuneTarget)
    {
      glm::vec2 entitySize = entities[i]->getSize();
      float radie = entitySize.x > entitySize.y ? entitySize.x : entitySize.y;
      glm::vec2 temp = entities[i]->getPosition();
      float distance = glm::distance(entities[i]->getPosition(), _position);

      if (distance < radie)
      {
        entities[i]->projectileHit(momentum, 1.);
        printf("Hitting target!\n");
        _lifeTime = 0;
        return true;
      }
    }
  }
  return false;
}