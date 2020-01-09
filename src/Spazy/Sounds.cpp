
#include "Sounds.h"

KingPin::AudioEngine SoundSystem::_audioEngine;

void SoundSystem::loadSounds() {
  _audioEngine.loadSound(SOUNDS::EXPLOSION,
                         "src/Spazy/res/audio/explosion.wav");
  _audioEngine.loadSound(SOUNDS::SMALL_EXPLOSION,
                         "src/Spazy/res/audio/grenadeExplosion.wav");
  _audioEngine.loadSound(SOUNDS::LASER, "src/Spazy/res/audio/laser.mp3");
}

void SoundSystem::playSound(unsigned int sound) {
    _audioEngine.playSound(sound);
}

void SoundSystem::update()
{
    _audioEngine.update();
}