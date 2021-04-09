/*!*************************************************************************
****
\file music.cpp
\par Project: Hookshot
\authors: Tan Egi (80%)
          Tan Wei Wen (20%)
\par DP email: egi.tan@digipen.edu
               t.weiwen@digipen.edu
\date 090421

\brief
This is the implementation file for the music system.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

****************************************************************************
***/
#include "music.h"

static FMOD_RESULT result;
static FMOD::Sound* music = nullptr;
static FMOD::System* music_system = nullptr;
static FMOD::Channel* channel = nullptr;

void music_Load(const char* file)
{
    // Create the main system object.
    result = FMOD::System_Create(&music_system);

    // Initialize FMOD.
    if (result == FMOD_OK)
        music_system->init(8, FMOD_INIT_NORMAL, nullptr);

    // Create the sound.
    result = music_system->createSound(file, FMOD_LOOP_NORMAL, 0, &music);
}


void music_Initialize()
{
    // Play the sound.
    music_system->playSound(music, 0, false, &channel);

    if (sound_mute == true)
        music_mute(true);
}

void music_Free()
{
    channel->stop();
}

void music_Unload()
{
    // Clean up.
    music->release();
    music_system->release();
}

void music_play(bool play_music)
{
    switch (play_music)
    {
        case true:
            // music play
            channel->setPaused(false);
            break;
        case false:
            // music pause
            channel->setPaused(true);
            break;
    }
}

void music_mute(bool mute)
{
    switch (mute)
    {
    case true:
        // music mute
        channel->setMute(true);
        break;
    case false:
        // music play
        channel->setMute(false);
        break;
    }
}
