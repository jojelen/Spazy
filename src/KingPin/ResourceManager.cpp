#include "ResourceManager.h"

namespace KingPin
{
TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::getTexture(std::string texturePath)
{
  return _textureCache.getTexture(texturePath);
}
} // namespace KingPin