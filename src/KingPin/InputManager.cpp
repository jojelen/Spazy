#include "InputManager.h"

namespace KingPin
{
InputManager::InputManager() : _mouseCoords(0.0f, 0.0f)
{
}

InputManager::~InputManager()
{
}

void InputManager::pressKey(unsigned int keyID)
{
  _keyMap[keyID] = true;
}
void InputManager::releaseKey(unsigned int keyID)
{
  _keyMap[keyID] = false;
}
// Checks if the key is pressed
bool InputManager::isKeyDown(unsigned int keyID)
{
  auto it = _keyMap.find(keyID);
  if (it != _keyMap.end())
    return it->second;
  else
    return false;
}

void InputManager::update()
{
  // Copies over the keyMap to previous key map
  for (auto &it : _keyMap)
  {
    _previousKeyMap[it.first] = it.second;
  }
}
bool InputManager::isKeyPressed(unsigned int keyID)
{
  // Check if the key was pressed this frame
  if (isKeyDown(keyID) == true && wasKeyPressed(keyID) == false)
  {
    return true;
  }
  return false;
}

bool InputManager::wasKeyPressed(unsigned int keyID)
{
  auto it = _previousKeyMap.find(keyID);
  if (it != _previousKeyMap.end())
    return it->second;
  else
    return false;
}

void InputManager::setMouseCoords(float x, float y)
{
  _mouseCoords.x = x;
  _mouseCoords.y = y;
}

} // namespace KingPin