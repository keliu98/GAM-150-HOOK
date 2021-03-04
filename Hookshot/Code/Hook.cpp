/*!*************************************************************************
****
\file hookshot.cpp
\authors: Tan Wei Wen

\par DP email:  t.weiwen@digipen.edu

\par Course: CSD 1450
\par Project: Software Engineering Project 2
\date 280221


\brief //TODO

****************************************************************************
***/

#include "pch.h"

AEVec2 cursor_pos;

int cursor_x;
int cursor_y;

void hook_update()
{	
	//temporary input, will need to translate as the camera moves ....
	AEInputGetCursorPosition(&cursor_x, &cursor_y);
	cursor_x = cursor_x - WINDOW_WIDTH / 2;
	cursor_y = (cursor_y - WINDOW_HEIGHT / 2) * -1;


	Input_g_mode(cursor_x, cursor_y);
}