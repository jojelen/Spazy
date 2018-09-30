#include "PopUp.h"
#include "KingPin/ResourceManager.h"

#include <iostream>

PopUp::PopUp(const glm::vec2 &position, int lifetime, PopID popID)
{
  switch (popID)
  {
  case plusOne:
    _textureID = KingPin::ResourceManager::getTexture("src/Spazy/res/textures/1.png").id;
    _width = 20.0f;
    _height = 20.0f;
    break;
  case start:
    _textureID =
        KingPin::ResourceManager::getTexture("src/Spazy/res/textures/start.png").id;
    _width = 300.0f;
    _height = 600.0f;
    break;
  case gameOver:
    _textureID =
        KingPin::ResourceManager::getTexture("src/Spazy/res/textures/gameover.png").id;
    _width = 300.0f;
    _height = 600.0f;
    break;

  default:
    std::cout << "Failed initializing popup!\n";
    break;
  }

  // Set position
  _position = position;

  _lifetime = lifetime;
  _life = lifetime;
}

bool PopUp::draw(KingPin::SpriteBatch &spriteBatch)
{
  glm::vec4 destRect(_position.x, _position.y, _width, _height);

  const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

  float lifePercent = (float)_life / (float)_lifetime;
  KingPin::Color color(255, 255, 255, (int)(255 * lifePercent));
  float angle = 1.577;

  spriteBatch.draw(destRect, angle, uvRect, _textureID, 1.0f, color);

  if (_life == 0)
    return true;
  else
  {
    _life--;
  }
  return false;
}

PopUp::~PopUp() {}
