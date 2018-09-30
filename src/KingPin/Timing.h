#pragma once

namespace KingPin
{

class FpsLimiter
{
public:
  FpsLimiter();
  void init(float maxFPS);

  void setMaxFPS(float maxFPS);

  void begin();
  //end will return the current FPS
  float end();

private:
  float _maxFPS, _fps, _frameTime;
  unsigned int _startTicks;

  void calculateFPS();
};
} // namespace KingPin