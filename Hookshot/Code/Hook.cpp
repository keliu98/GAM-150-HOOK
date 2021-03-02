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

		//----------------------------PHASE 1: FIRING------------------------------------
		//Storing the pivot position
		if (hook->hook_state == not_firing)
		{
			AEVec2Set(&hook->pivot_pos, static_cast<float>(cursor_x), static_cast<float>(cursor_y));
			hook->hook_state = firing;
		}

		//Getting the pivot angle
		AEVec2 dir_vec;
		AEVec2Sub(&dir_vec, &hook->pivot_pos, &character->pos);
		AEVec2Normalize(&dir_vec, &dir_vec);
		hook->pivot_angle = static_cast<float>(atan2(dir_vec.y, dir_vec.x));

		//Getting the max_len
		hook->max_len = AEVec2Distance(&hook->pivot_pos, &character->pos);

		//Getting the various position of the hook
		AEVec2 tail_pos = character->pos;//tail
		
		AEVec2 head_pos;
		AEVec2Scale(&head_pos, &dir_vec, hook->curr_len);
		AEVec2Add(&head_pos, &tail_pos, &head_pos);//head

		AEVec2Add(&hook->center_pos, &head_pos, &tail_pos);
		AEVec2Scale(&hook->center_pos, &hook->center_pos, 0.5f);//center

		//Scaling the hook length
		if(hook->hook_state == firing)
			hook->curr_len += 10;

		//~~TODO REPLACE WITH THE COLLISION EVENTUALLY TO DETECT IF IT HIT A WALL
		if (hook->curr_len > hook->max_len)
		{
			hook->hook_state = first_tether;
			head_pos = hook->pivot_pos;
		}

		//---------------------PHASE 2: FIRST TETHER-----------------------------------
		//Adjusting the length to always be the max_len
		if (hook->hook_state == first_tether)
		{
			hook->curr_len = hook->max_len;

			//Getting the pivot again
			AEVec2 dir_vec;
			AEVec2Sub(&dir_vec, &hook->pivot_pos, &character->pos);
			AEVec2Normalize(&dir_vec, &dir_vec);
			hook->pivot_angle = static_cast<float>(atan2(dir_vec.y, dir_vec.x));

			//Getting the arc tangent angle = sin 0
			hook->arc_tan = sin(hook->pivot_angle);

			//Magnitude of current velocity to translate it to a swing direction
			
		}

		

		//---------------------PHASE 3: TETHERED AND SWINGING-----------------------------------

		if (hook->hook_state == tethered)
		{
			hook->curr_len = hook->max_len;
		}
		




			

	}

	if (AEInputCheckReleased(AEVK_LBUTTON))
	{
		hook->flag = false;
		hook->hook_state = not_firing;
		hook->curr_len = 0;
	}

}