//#pragma once
#include "pch.h"

#ifndef LEVELUI_H
#define LEVELUI_H
enum font_type
{
	NORMAL,
	ITALIC,
	SMALL,
};

void PrintText(char* message, int type, AEVec2 position);
void UpdateButton();
void UpdatePauseMenu();
void switchbuttonstate(int state);

#endif