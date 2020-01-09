#pragma once

#include "Fmod.h"
#include "fmod.hpp"

#include <string>
#include <unordered_map>

namespace KingPin {

class AudioEngine {
public:
  AudioEngine();
  ~AudioEngine();

  void playSound(unsigned int sound);
  void loadSound(unsigned int sound, const std::string &soundFile);
  void update();
private:
  void init();
  void checkFmodResults(FMOD_RESULT result);

  FMOD::System *_system;
  std::unordered_map<unsigned int, FMOD::Sound*> _sounds;
  FMOD::Channel *_channel = 0;
};

} // namespace KingPin