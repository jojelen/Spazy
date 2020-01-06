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

  void playSound(const std::string &sound);
  void loadSound(const std::string &sound, const std::string &soundFile);

private:
  void init();
  void checkFmodResults(FMOD_RESULT result);

  FMOD::System *_system;
  std::unordered_map<std::string, FMOD::Sound*> _sounds;
  FMOD::Channel *_channel = 0;
};

} // namespace KingPin