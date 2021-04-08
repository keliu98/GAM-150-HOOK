#pragma once
#include "pch.h"

void music_Load(const char* file);
void music_Initialize();
void music_play(bool stopMusic);
void music_mute(bool mute);
void music_Unload();
void music_Free();
