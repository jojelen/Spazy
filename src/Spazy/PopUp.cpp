#include "PopUp.h"
#include "KingPin/ResourceManager.h"

#include <iostream>
#include <vector>

Effect::Effect() {}

Effect::~Effect() {}

//-----------------------------------------------------------------------------

Explosion::Explosion(const glm::vec2 &pos, const float size)
{
  _textureID = KingPin::ResourceManager::getTexture(
                   "src/Spazy/res/textures/smallExplosion1.png")
                   .id;
  _width = 1.0f;
  _height = 1.0f;

  // Set position
  _position = pos;
  _size = size;
  _lifetime = 30;
  _life = 30;

  // std::cout << "Creating explosion!\n"; // DEBUG
}

Explosion::~Explosion() {}

bool Explosion::draw(KingPin::SpriteBatch &spriteBatch)
{
  static const int totTextures = 6; // Number of textures in animation
  static std::vector<int> textureIDs;
  for (int i = 1; i <= totTextures; ++i)
    textureIDs.push_back( KingPin::ResourceManager::getTexture(
                   "src/Spazy/res/textures/smallExplosion" + std::to_string(i)+".png")
                   .id);

  float lifeFraction = (float)_life / (float)_lifetime;

  _width = _size * (1. - lifeFraction);
  _height = _size * (1. - lifeFraction);

  glm::vec4 destRect(_position.x, _position.y, _width, _height);

  static const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);

  KingPin::Color color(255, 255, 255, (int)(255 * lifeFraction));

  static constexpr float angle = 1.577;

  // Drawing the explosion. The texture is determined by the lifeFraction
  spriteBatch.draw(destRect, angle, uvRect, textureIDs[(int)( (1-lifeFraction) * totTextures)], 1.0f, color);
  
  if (_life == 0)
    return true;
  else
  {
    _life--;
  }

  return false;
}

//-----------------------------------------------------------------------------

PopUp::PopUp(const glm::vec2 &position, int lifetime, PopID popID)
{
  switch (popID)
  {
  case plusOne:
    _textureID =
        KingPin::ResourceManager::getTexture("src/Spazy/res/textures/1.png").id;
    _width = 20.0f;
    _height = 20.0f;
    break;
  case start:
    _textureID =
        KingPin::ResourceManager::getTexture("src/Spazy/res/textures/start.png")
            .id;
    _width = 300.0f;
    _height = 600.0f;
    break;
  case gameOver:
    _textureID = KingPin::ResourceManager::getTexture(
                     "src/Spazy/res/textures/gameover.png")
                     .id;
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

  float lifeFraction = (float)_life / (float)_lifetime;
  KingPin::Color color(255, 255, 255, (int)(255 * lifeFraction));
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
