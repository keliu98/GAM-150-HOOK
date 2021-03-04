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

static float SWING_ACCELERATION = 300;
static float HOOK_SPEED = 20;

AEVec2 cursor_pos;
int cursor_x;
int cursor_y;

float intial_angle;

enum swing_dir
{
	NO_DIR,
	CLOCKWISE,
	ANTI_CLOCKWISE,

}swing_dir;

float calculate_pivot();
float calculate_arc();
void calculate_positions(AEVec2 &dir_vec);

void hook_update()
{	
	//temporary input, will need to translate as the camera moves ....
	AEInputGetCursorPosition(&cursor_x, &cursor_y);
	cursor_x = cursor_x - WINDOW_WIDTH / 2;
	cursor_y = (cursor_y - WINDOW_HEIGHT / 2) * -1;

	if (AEInputCheckCurr(AEVK_LBUTTON))
	{
		//----------------------------PHASE 1: FIRING------------------------------------
		//About to fire
		if (hook->hook_state == not_firing)
		{
			//Set flag to active
			hook->flag = true;

			//Setting the pivot pos to the mouse cusor
			AEVec2Set(&hook->pivot_pos, static_cast<float>(cursor_x), static_cast<float>(cursor_y));

			//setting the mode
			hook->hook_state = firing;
		}

		//Fired and trying to tether 
		if (hook->hook_state == firing)
		{
			//Getting the max_len added 0.5f for some lee way...
			hook->max_len = AEVec2Distance(&hook->pivot_pos, &character->pos) + 0.5f;

			//Getting the pivot angle and directional vector
			AEVec2 dir_vec;
			hook->pivot_angle = calculate_pivot();
			AEVec2FromAngle(&dir_vec, hook->pivot_angle);

			//Getting the various position of the hook
			calculate_positions(dir_vec);

			//Increasing the hook length
			hook->curr_len += HOOK_SPEED;

			//~~TODO REPLACE WITH THE COLLISION EVENTUALLY TO DETECT IF IT HIT A WALL
			if (hook->curr_len > hook->max_len)
			{
				//need to set head_pos to pivot_pos -> current_length
				hook->curr_len = hook->max_len;
				hook->hook_state = tethered;
			}
		}


		//---------------------PHASE 2: TETHERED AND SWINGING-----------------------------------

		if (hook->hook_state == tethered)
		{
			//Getting the pivot angle again
			AEVec2 dir_vec;
			hook->pivot_angle = calculate_pivot();
			AEVec2FromAngle(&dir_vec, hook->pivot_angle);

			//Center_pos for rendering
			calculate_positions(dir_vec);

			//Getting the arc tangent angle
			hook->arc_tan = calculate_arc();

			//Getting the character velocity magnitude so that it can be conserved
			float magnitude = AEVec2Length(&character->velocity);

			//Creating the directional vector based on the angle of the arc tan
			AEVec2 dir_vec_arc;
			AEVec2FromAngle(&dir_vec_arc, hook->arc_tan);

		
			if (magnitude < 30.0f)
			{
				/*switch (swing_dir)
				{
					case(CLOCKWISE)
						swing_dir = ANTI_CLOCKWISE;
						break;

						case(CLOCKWISE)
						swing_dir = ANTI_CLOCKWISE;
						break;
				}*/
				
				//1 = anti clock wise, 2 = clockwise 
				if (swing_dir == CLOCKWISE)
				{
					swing_dir = ANTI_CLOCKWISE;
				}

				if (swing_dir == ANTI_CLOCKWISE)
				{
					swing_dir = CLOCKWISE;
				}
					
			}

			//Scaling the new velocity direction with the old velocity magnitude
			AEVec2Scale(&dir_vec_arc, &dir_vec_arc, magnitude);
			character->velocity = dir_vec_arc;


			//NOTE TO SELF TO ADJUST LENGTH OF HOOK NEED TO CHANGE BOTH
			//hook->max_len -= 2;
			//hook->curr_len -= 2;

		}
	}

	//---------------------PHASE 4: RELEASING-----------------------------------
	if (AEInputCheckReleased(AEVK_LBUTTON))
	{
		hook->flag = false;
		hook->hook_state = not_firing;
		hook->curr_len = 0;
		hook->max_len = 0;

		swing_dir = NO_DIR;

		//TODO CONSERVE MOMENTUM WHEN RELEASED.
	}

}

//function for reseting the character position to stay within the arc
void hook_char_pos_update()
{
	float distance = AEVec2Distance(&hook->pivot_pos, &character->pos);

	if (distance > hook->max_len || distance < hook->max_len)
	{
		//Getting the distance to translate it by, only need to translate it by exceeding distance
		distance = distance - hook->max_len;

		//Creating the directional vector
		AEVec2 dir_vec;
		AEVec2FromAngle(&dir_vec, hook->pivot_angle);

		//Scaling the directional vector by the distance
		AEVec2Scale(&dir_vec, &dir_vec, distance);

		//Setting the position
		AEVec2Add(&character->pos, &character->pos, &dir_vec);
	}
}


float calculate_pivot()
{
	AEVec2 dir_vec;
	AEVec2Sub(&dir_vec, &hook->pivot_pos, &character->pos);
	AEVec2Normalize(&dir_vec, &dir_vec);
	return static_cast<float>(atan2(dir_vec.y, dir_vec.x));
}

float calculate_arc()
{
	if (swing_dir == NO_DIR)
	{
		//inverting movement when aiming for top left of character
		if (hook->pivot_angle > 0 && hook->pivot_angle < PI / 2)
		{
			swing_dir = ANTI_CLOCKWISE;
			return hook->pivot_angle - PI / 2;
		}

		//inverting movement when aiming for bottom left of character
		if (hook->pivot_angle < 0 && hook->pivot_angle > -(PI / 2))
		{
			swing_dir = ANTI_CLOCKWISE;
			return hook->pivot_angle - PI / 2;
		}

		swing_dir = CLOCKWISE;
		return hook->pivot_angle + PI / 2;
	}

	if (swing_dir == ANTI_CLOCKWISE)
		return hook->pivot_angle - PI / 2;

	if (swing_dir == CLOCKWISE)
		return hook->pivot_angle + PI / 2;
}

void calculate_positions(AEVec2& dir_vec)
{
	hook->tail_pos = character->pos;							    //tail = character pos

	AEVec2Scale(&hook->head_pos, &dir_vec, hook->curr_len);
	AEVec2Add(&hook->head_pos, &hook->tail_pos, &hook->head_pos);	//head = len + tail

	AEVec2Add(&hook->center_pos, &hook->head_pos, &hook->tail_pos);
	AEVec2Scale(&hook->center_pos, &hook->center_pos, 0.5f);	    //center the mid point
}

