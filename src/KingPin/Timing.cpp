#include "Timing.h"

#include <SDL/SDL.h>

namespace KingPin
{
FpsLimiter::FpsLimiter()
{
}

void FpsLimiter::init(float maxFPS)
{
  setMaxFPS(maxFPS);
}

void FpsLimiter::begin()
{
  _startTicks = SDL_GetTicks();
}
void FpsLimiter::setMaxFPS(float maxFPS)
{
  _maxFPS = maxFPS;
}

//end will return the current FPS
float FpsLimiter::end()
{

  calculateFPS();

  float frameTicks = SDL_GetTicks() - _startTicks;
  //Limit the fps to _maxFPS
  if (1000.0f / _maxFPS > frameTicks)
  {
    SDL_Delay(1000.0f / _maxFPS - frameTicks);
  }

  return _fps;
}

void FpsLimiter::calculateFPS()
{
  static const int NUM_SAMPLES = 100;
  static float frameTimes[NUM_SAMPLES];
  static int currentFrame = 0;

  static float prevTicks = SDL_GetTicks();
  float currentTicks;
  currentTicks = SDL_GetTicks();
  _frameTime = currentTicks - prevTicks;
  frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

  prevTicks = currentTicks;
  int count;

  currentFrame++;
  if (currentFrame < NUM_SAMPLES)
  {
    count = currentFrame;
  }
  else
  {
    count = NUM_SAMPLES;
  }

  float frameTimeAverage = 0;
  for (int i = 0; i < count; i++)
    frameTimeAverage += frameTimes[i];
  frameTimeAverage /= count;

  if (frameTimeAverage > 0)
  {
    _fps = 1000.0f / frameTimeAverage;
  }
  else
  {
    _fps = 60.0f;
  }
}

} // namespace KingPin