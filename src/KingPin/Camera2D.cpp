#include "Camera2D.h"
#include <iostream>

namespace KingPin
{
Camera2D::Camera2D()
    : _position(0.0f, 0.0f), _cameraMatrix(1.0f), _orthoMatrix(1.0f),
      _scale(1.0f), _needsMatrixUpdate(true), _screenWidth(500),
      _screenHeight(500) {}

Camera2D::~Camera2D() {}

void Camera2D::init(int screenWidth, int screenHeight)
{
  _screenWidth = screenWidth;
  _screenHeight = screenHeight;
  _orthoMatrix =
      glm::ortho(-(float)_screenWidth / 2.0f, (float)_screenWidth / 2.0f,
                 -(float)_screenHeight / 2.0f, (float)_screenHeight / 2.0f);
}

void Camera2D::update()
{
  if (_needsMatrixUpdate)
  {

    // Camera translation
    glm::vec3 translate(-_position.x, -_position.y, 0.0f);
    _cameraMatrix = glm::translate(_orthoMatrix, translate);

    // Camera Scale
    glm::vec3 scale(_scale, _scale, 1.0f);
    _cameraMatrix = glm::scale(_cameraMatrix, scale);

    _needsMatrixUpdate = false;
  }
}

glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords)
{

  // Invert Y direction
  screenCoords.y = _screenHeight - screenCoords.y;
  // Changes origo to center
  screenCoords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
  // Translate with the camera position
  screenCoords += _position;
  // Scales the coordinates
  screenCoords /= _scale;

  return screenCoords;
}

} // namespace KingPin