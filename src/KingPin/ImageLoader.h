#pragma once

#include "GLTexture.h"
#include <string>

namespace KingPin
{
class ImageLoader
{
public:
  static GLTexture loadPNG(std::string filePath);
};

} // namespace KingPin