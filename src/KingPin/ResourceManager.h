#pragma once

#include <map>
#include "TextureCache.h"
#include <string>

namespace KingPin
{
class ResourceManager
{
public:
  // Gets a GLTexture from the cashe, or loads it if it is not there.
  static GLTexture getTexture(std::string texturePath);

private:
  // The TextureCache contains a map of all the GLTextures that have been
  // loaded from png files.
  static TextureCache _textureCache;
};

} // namespace KingPin