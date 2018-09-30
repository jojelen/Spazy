#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>

namespace KingPin
{
TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string texturePath)
{
  //look up the texture and se if it is in the map
  auto mit = _textureMap.find(texturePath);
  //auto makes it into
  //std::map<std::string,GLTexture>::iterator mit = _textureMap.find(texturePath);

  //If it is not in the cached textures, need to load it.
  if (mit == _textureMap.end())
  {
    GLTexture newTexture = ImageLoader::loadPNG(texturePath);

    _textureMap.insert(make_pair(texturePath, newTexture));

    std::cout << "Loaded texture!\n";
    return newTexture;
  }

  //std::cout << "Cached texture\n";
  return mit->second;
}

} // namespace KingPin