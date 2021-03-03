#include"pch.h"

void Input() {
	float delta_time = g_dt;
	float CHARACTER_ACCEL_HORI = 500.0f;

	// Handling Input
	AEInputUpdate(); 

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

	if (AEInputCheckTriggered(AEVK_W) && hook->flag == false)
	{
		character->velocity.y += CHAR_HEIGHT_VEL;
	}

	hook_update();
	physics_update();
}