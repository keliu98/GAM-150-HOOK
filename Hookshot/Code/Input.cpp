#include"pch.h"
#include"collision.h"
void Input_g_mode() {
	float CHARACTER_ACCEL_HORI = 500.0f;

	//Keyboard
	if (AEInputCheckCurr(AEVK_A))
	{
		AEVec2 dir = { -1.0f, 0.0f };
		set_accel_to_vel(character->velocity, dir, CHARACTER_ACCEL_HORI);
	}

	if (AEInputCheckCurr(AEVK_D))
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

	if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
	{
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

//For interracting with the main menu
void Input_menu_mode()
{
	int cursor_x;
	int cursor_y;

	//temporary input, will need to translate as the camera moves ....
	AEInputGetCursorPosition(&cursor_x, &cursor_y);

	//centering the cursor_positiond

	translate_cursor(cursor_x, cursor_y);

	AEVec2 mouse_pos{ static_cast <float>(cursor_x), static_cast <float>(cursor_y) };
	//TODO create AABB for button-> dont put it here, can just intialse it with the AABB as the button is static. 

	for (Button& button : buttons)
	{
		if (AEInputCheckTriggered(AEVK_LBUTTON) && CollisionIntersection_PointRect(mouse_pos, button.aabb))
		{
			if (button.type == TITLE) {
				next = GS_LEVEL1;
			}
			//TODO is what happens after you click -> e.g changing to different screen or etc
		}


	}
}
