
#include "Sounds.h"

void loadSounds(KingPin::AudioEngine &audioEngine) {
  audioEngine.loadSound("explosion", "src/Spazy/res/audio/explosion.wav");
  audioEngine.loadSound("smallExplosion",
                        "src/Spazy/res/audio/grenadeExplosion.wav");
                        audioEngine.loadSound("laser",
                        "src/Spazy/res/audio/laser.mp3");
}

void playSound(const std::string &sound) {
  static KingPin::AudioEngine audioEngine;
  static bool sounds_loaded = false;
  if (!sounds_loaded) {
    loadSounds(audioEngine);
    sounds_loaded = true;
  }
  audioEngine.playSound(sound);
}