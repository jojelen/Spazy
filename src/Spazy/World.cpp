#include "World.h"
#include "KingPin/ResourceManager.h"
#include <glm/glm.hpp>

World::World() {}

World::~World() {}

void World::init()
{
  // Texture of background
  _textureID =
      KingPin::ResourceManager::getTexture("src/Spazy/res/textures/space.png").id;

  _spriteBatch.init();
  _spriteBatch.begin();
  const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
  KingPin::Color color;
  color.r = 255;
  color.g = 255;
  color.b = 255;
  color.a = 255;
  for (int i = 0; i < 4; i++)
  {
    glm::vec4 destRect(-1024.0f + i * 512.0f, -512.0f, 512.0f, 1024.0f);
    _spriteBatch.draw(destRect, uvRect, _textureID, 1.0f, color);
  }
  _spriteBatch.end();
}
void World::draw() { _spriteBatch.renderBatch(); }