#pragma once

#include <map>
#include <string>
#include "GLTexture.h"

namespace KingPin
{
class TextureCache
{
public:
  TextureCache();
  ~TextureCache();

  // Retrieves a texture, either from the cache or
  // loaded from the texturePath
  GLTexture getTexture(std::string texturePath);

private:
  // A map that stores all the textures so that one does
  // not have to load a texture a multiple of times
  std::map<std::string, GLTexture> _textureMap;
};
} // namespace KingPin
