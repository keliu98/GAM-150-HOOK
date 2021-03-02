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
static float SWING_ACCELERATION = 100;
static float PI = 3.141592f;

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
			//Setting the pivot pos to the mouse cusor
			AEVec2Set(&hook->pivot_pos, static_cast<float>(cursor_x), static_cast<float>(cursor_y));

			//Getting the max_len
			hook->max_len = AEVec2Distance(&hook->pivot_pos, &character->pos);

			//setting the mode
			hook->hook_state = firing;
		}

		//Getting the pivot angle
		AEVec2 dir_vec;
		AEVec2Sub(&dir_vec, &hook->pivot_pos, &character->pos);
		AEVec2Normalize(&dir_vec, &dir_vec);
		hook->pivot_angle = static_cast<float>(atan2(dir_vec.y, dir_vec.x));

		//Getting the various position of the hook
		AEVec2 tail_pos = character->pos;//tail

		AEVec2 head_pos;
		AEVec2Scale(&head_pos, &dir_vec, hook->curr_len);
		AEVec2Add(&head_pos, &tail_pos, &head_pos);//head

		AEVec2Add(&hook->center_pos, &head_pos, &tail_pos);
		AEVec2Scale(&hook->center_pos, &hook->center_pos, 0.5f);//center

		//Scaling the hook length
		if (hook->hook_state == firing)
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

			//Getting the pivot angle again
			AEVec2 dir_vec;
			AEVec2Sub(&dir_vec, &hook->pivot_pos, &character->pos);
			AEVec2Normalize(&dir_vec, &dir_vec);
			hook->pivot_angle = static_cast<float>(atan2(dir_vec.y, dir_vec.x));

			//Angle perpendicular to the pivot angle
			hook->arc_tan = hook->pivot_angle + PI / 2;

			//Getting the character velocity magnitude so that it can be conserved
			float magnitude = AEVec2Length(&character->velocity);

			//Creating the directional vector based on the angle of the arc tan
			AEVec2 arc_tan_vel;
			AEVec2FromAngle(&arc_tan_vel, hook->arc_tan);

			//inverting movement for top left
			if (hook->pivot_angle > 0 && hook->pivot_angle < PI / 2)
				AEVec2Scale(&arc_tan_vel, &arc_tan_vel, -1.0f);

			//inverting movement for bottom right
			if (hook->pivot_angle < 0 && hook->pivot_angle > -(PI / 2))
				AEVec2Scale(&arc_tan_vel, &arc_tan_vel, -1.0f);

			//Scaling the new velocity direction with the old velocity magnitude
			AEVec2Scale(&arc_tan_vel, &arc_tan_vel, magnitude);
			character->velocity = arc_tan_vel;

			hook->hook_state = tethered;
		}



		//---------------------PHASE 3: TETHERED AND SWINGING-----------------------------------

		if (hook->hook_state == tethered)
		{
			hook->curr_len = hook->max_len;

			//Getting the pivot angle again
			AEVec2 dir_vec;
			AEVec2Sub(&dir_vec, &hook->pivot_pos, &character->pos);
			AEVec2Normalize(&dir_vec, &dir_vec);
			hook->pivot_angle = static_cast<float>(atan2(dir_vec.y, dir_vec.x));

			//Getting the arc tangent angle
			hook->arc_tan = hook->pivot_angle + PI / 2;


			//~~~~MIGHT NOT BE NECCESSARY, TBC~~~
			//Creating the directional vector based on the angle of the arc tan
			AEVec2 arc_tan_dir;
			AEVec2FromAngle(&arc_tan_dir, hook->arc_tan);

			//inverting movement for top left
			if (hook->pivot_angle > 0 && hook->pivot_angle < PI / 2)
				AEVec2Scale(&arc_tan_dir, &arc_tan_dir, -1.0f);

			//inverting movement for bottom right
			if (hook->pivot_angle < 0 && hook->pivot_angle > -(PI / 2))
				AEVec2Scale(&arc_tan_dir, &arc_tan_dir, -1.0f);

			set_accel_to_vel(character->velocity, arc_tan_dir, SWING_ACCELERATION);
			//~~~~MIGHT NOT BE NECCESSARY, TBC~~~
		}
	}

	if (AEInputCheckReleased(AEVK_LBUTTON))
	{
		hook->flag = false;
		hook->hook_state = not_firing;
		hook->curr_len = 0;
	}

}