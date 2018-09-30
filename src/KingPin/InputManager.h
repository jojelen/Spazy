#pragma once

#include <unordered_map>
#include <glm/glm.hpp>

namespace KingPin
{

class InputManager
{
public:
  InputManager();
  ~InputManager();

  void update();

  void pressKey(unsigned int keyID);

  void releaseKey(unsigned int keyID);

  // Returns true if the key is down
  bool isKeyDown(unsigned int keyID);

  // Returns true if the key wassjust pressed
  bool isKeyPressed(unsigned int keyID);

  void setMouseCoords(float x, float y);
  glm::vec2 getMouseCoords() const { return _mouseCoords; };

private:
  // Returns true if the key wassjust pressed
  bool wasKeyPressed(unsigned int keyID);

  // Map that keeps track of the keys that are pressed
  std::unordered_map<unsigned int, bool> _keyMap;
  std::unordered_map<unsigned int, bool> _previousKeyMap;
  glm::vec2 _mouseCoords;
};

} // namespace KingPin
