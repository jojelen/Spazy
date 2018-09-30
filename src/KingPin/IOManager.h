#pragma once

#include <string>
#include <vector>

namespace KingPin
{
class IOManager
{
public:
  static bool readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer);
};
} // namespace KingPin
