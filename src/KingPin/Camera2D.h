#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace KingPin
{

// Camera for 2D games
class Camera2D
{
public:
  Camera2D();
  ~Camera2D();

  // sets up the orthographic matrix and screen dimensions
  void init(int screenWidth, int screenHeight);
  // updates the camera matrix if needed
  void update();

  // Function that convert screen coordinates to world coordinates
  glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);
  // Function that converts pixelsize to normalized coordinates
  glm::vec4 convertPixelsToNormalized(glm::vec4 pixels);
  glm::vec2 convertNormalizedToPixels(glm::vec2 norm);

  void setPosition(const glm::vec2 &newPosition)
  {
    _position = newPosition;
    _needsMatrixUpdate = true;
  };

  void setScale(const float newScale)
  {
    _scale = newScale;
    if (_scale < 0.01)
      _scale = 0.01;
    _needsMatrixUpdate = true;
  };

  glm::vec2 getPosition() { return _position; };
  glm::mat4 getCameraMatrix() { return _cameraMatrix; };
  float getScale() { return _scale; }

private:
  glm::vec2 _position; // position of camera
  glm::mat4 _cameraMatrix, _orthoMatrix;
  bool _needsMatrixUpdate; // True if the camera should move or zoom
  float _scale;
  int _screenWidth, _screenHeight;
};
} // namespace KingPin
