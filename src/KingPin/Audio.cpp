#include "Audio.h"
#include "fmod.hpp"
#include "fmod_errors.h"

#include <iostream>

namespace KingPin {

AudioEngine::AudioEngine() { init(); }

AudioEngine::~AudioEngine() {

  FMOD_RESULT result;

  for (auto &sound : _sounds) 
    checkFmodResults(sound.second->release());
  _sounds.clear();
  checkFmodResults(_system->close());
  checkFmodResults(_system->release());
}

void AudioEngine::playSound(const std::string &sound) {
  auto playable_sound = _sounds.find(sound);

  if (playable_sound == _sounds.end())
    std::cout << "[ERROR]: " << sound << " sound not found!\n";
  else 
    checkFmodResults(
        _system->playSound(playable_sound->second, 0, false, &_channel));
}

void AudioEngine::loadSound(const std::string &sound,
                            const std::string &soundFile) {
  auto playable_sound = _sounds.find(sound);

  if (playable_sound != _sounds.end())
    std::cout << "[ERROR]: sound already loaded!\n";
  else {
    _sounds[sound] = nullptr;
    checkFmodResults(_system->createSound(soundFile.c_str(), FMOD_DEFAULT,
                                              0, &_sounds[sound]));
  }
}

void AudioEngine::init() {
    
  unsigned int version;
  void *extradriverdata = 0;

  Common_Init(&extradriverdata);

  /*
      Create a System object and initialize
  */
  checkFmodResults(FMOD::System_Create(&_system));
  checkFmodResults(_system->getVersion(&version));

  if (version < FMOD_VERSION) {
    std::cout << "FMOD lib version " << version
              << " doesn't match header version " << FMOD_VERSION << std::endl;
  }

  checkFmodResults(_system->init(32, FMOD_INIT_NORMAL, extradriverdata));
}

void AudioEngine::checkFmodResults(FMOD_RESULT result) {
  if (result != FMOD_OK) {
    std::cout << "[ERROR]: AudioEngine: " << FMOD_ErrorString(result)
              << std::endl;
  }
}

} // namespace KingPin