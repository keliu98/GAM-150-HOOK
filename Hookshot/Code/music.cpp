#include "music.h"

static FMOD_RESULT result;
static FMOD::Sound* music = nullptr;
static FMOD::System* music_system = nullptr;
static FMOD::Channel* channel = nullptr;


void music_Load()
{
    // Create the main system object.
    result = FMOD::System_Create(&music_system);

    // Initialize FMOD.
    if (result == FMOD_OK)
        music_system->init(8, FMOD_INIT_NORMAL, nullptr);
}


void music_Initialize(const char* file) // "../Music/bensound-ukulele.mp3"
{
    // Create the sound.
    result = music_system->createSound(file, FMOD_LOOP_NORMAL, 0, &music);

    // Play the sound.
    music_system->playSound(music, 0, false, &channel);
}

void music_Free()
{
    // Clean up.
    music->release();
    music_system->release();
}

//
//void music_play(int music, bool stopMusic);
//void music_pause(bool, int);
//void music_stop(int);