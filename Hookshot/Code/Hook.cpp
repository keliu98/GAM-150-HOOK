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

	if (AEInputCheckCurr(AEVK_LBUTTON))
	{
		hook->flag = true;
		hook->center_pos.x = cursor_x;
		hook->center_pos.y = cursor_y;
		hook->curr_len += 10;

	}

	if (AEInputCheckReleased(AEVK_LBUTTON))
	{
		hook->flag = false;
		hook->curr_len = 0;
	}

}