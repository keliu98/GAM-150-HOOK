#pragma once
#include "pch.h"

void music_Load();
void music_Initialize(const char* file);
void music_play(bool stopMusic);
void music_mute(bool mute);
void music_Free();
