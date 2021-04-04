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

void music_play(bool play_music) // int music
{
    switch (play_music)
    {
        case true:
            channel->setPaused(false);
            std::cout << "Music: Play\n";
            break;
        case false:
            channel->setPaused(true);
            std::cout << "Music: Pause\n";
            break;
    }
}

void music_mute(bool mute)
{
    switch (mute)
    {
    case true:
        channel->stop();
        std::cout << "Music: Play\n";
        break;
    case false:
        music_system->playSound(music, 0, false, &channel);
        std::cout << "Music: Pause\n";
        break;
    }
}
