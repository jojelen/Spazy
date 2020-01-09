#pragma once
#include <KingPin/Audio.h>
#include <string>

enum SOUNDS
{
    EXPLOSION = 1,
    SMALL_EXPLOSION = 2,
    LASER = 3
};

class SoundSystem
{
    public:
    SoundSystem();
    ~SoundSystem();

    static void loadSounds();
    static void playSound(unsigned int sound);
    static void update();

    private:
    static KingPin::AudioEngine _audioEngine;
};


