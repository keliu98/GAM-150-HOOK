#include"pch.h"

void Input_g_mode() {
	float CHARACTER_ACCEL_HORI = 500.0f;

	//Keyboard
	if (character->grid_collision_flag != COLLISION_LEFT && AEInputCheckCurr(AEVK_A))
		// || (hook->hook_state == tethered && Flag != COLLISION_BOTTOM)
	{
		AEVec2 dir = { -1.0f, 0.0f };
		set_accel_to_vel(character->velocity, dir, CHARACTER_ACCEL_HORI);
	}

	if (character->grid_collision_flag != COLLISION_RIGHT && AEInputCheckCurr(AEVK_D))
	{
		AEVec2 dir = { 1.0f, 0.0f };
		set_accel_to_vel(character->velocity, dir, CHARACTER_ACCEL_HORI);
	}

	if (character->grid_collision_flag != COLLISION_TOP && (AEInputCheckTriggered(AEVK_W) ||
		AEInputCheckTriggered(AEVK_SPACE)) && hook->flag == false)
	{
		if (character->char_state != jumping)
		{
			character->velocity.y += CHAR_HEIGHT_VEL;
			character->char_state = jumping;
		}
	}

	if (AEInputCheckCurr(AEVK_R))
	{
		next = GS_RESTART;
	}


	//Mouse Press and position
	int cursor_x;
	int cursor_y;

	//temporary input, will need to translate as the camera moves ....
	AEInputGetCursorPosition(&cursor_x, &cursor_y);

	//centering the cursor_position
	cursor_x = cursor_x - WINDOW_WIDTH / 2;
	cursor_y = (cursor_y - WINDOW_HEIGHT / 2) * -1;

	translate_cursor(cursor_x, cursor_y);

	if (AEInputCheckCurr(AEVK_LBUTTON))
	{
		fire_hook(cursor_x, cursor_y);
	}

	if (AEInputCheckReleased(AEVK_LBUTTON))
	{
		release_hook();
	}

}
