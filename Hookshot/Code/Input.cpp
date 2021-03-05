#include"pch.h"

void Input_g_mode() {
	float CHARACTER_ACCEL_HORI = 500.0f;

	//Temporary for doing physics.cpp
	if (AEInputCheckCurr(AEVK_A) && hook->flag == false)
	{
		AEVec2 dir = { -1.0f, 0.0f };
		set_accel_to_vel(character->velocity, dir, CHARACTER_ACCEL_HORI);
	}

	if (AEInputCheckCurr(AEVK_D) && hook->flag == false)
	{
		AEVec2 dir = { 1.0f, 0.0f };
		set_accel_to_vel(character->velocity, dir, CHARACTER_ACCEL_HORI);
	}

	if ((AEInputCheckTriggered(AEVK_W) || AEInputCheckTriggered(AEVK_SPACE)) && hook->flag == false)
	{
		if (character->char_state != jumping)
		{
			character->velocity.y += CHAR_HEIGHT_VEL;
			character->char_state = jumping;
		}
	}

}

void Input_g_mode(int x, int y) {

	if (AEInputCheckCurr(AEVK_LBUTTON))
	{
		hook->flag = true;
		hook->center_pos.x = x;
		hook->center_pos.y = y;
		hook->curr_len += 10;

	}

	if (AEInputCheckReleased(AEVK_LBUTTON))
	{
		hook->flag = false;
		hook->curr_len = 0;
	}
}