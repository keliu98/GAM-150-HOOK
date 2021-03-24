#include"pch.h"
#include"collision.h"
void Input_g_mode() {
	float CHARACTER_ACCEL_HORI = 500.0f;

	AEInputUpdate();

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
	//Debug lives code
	if (AEInputCheckTriggered(AEVK_G))
	{
		TOTAL_LIVES--;
		if (TOTAL_LIVES == 0) {
			next = GS_MENU;
		}
		else
			std::cout << TOTAL_LIVES;
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
		next = GS_MENU;
	}

	if (AEInputCheckCurr(AEVK_H))
	{
		//std::cout << enemies[0].cliff_check.x <<"\n";
		//std::cout << enemies[0].pos.x << "\n";
		std::cout << GetCellValue(int(enemies[0].cliff_check.x), int(enemies[0].cliff_check.y));

	}


	//Mouse Press and position
	int cursor_x;
	int cursor_y;

	//temporary input, will need to translate as the camera moves ....
	AEInputGetCursorPosition(&cursor_x, &cursor_y);

	translate_cursor(cursor_x, cursor_y);

	if (AEInputCheckTriggered(AEVK_LBUTTON) && ammo > 0) {
		ammoD--;
		// std::cout << ammo;
	}

	if (AEInputCheckCurr(AEVK_LBUTTON) && ammo > 0)
	{
		fire_hook(cursor_x, cursor_y);

	}

	if (AEInputCheckReleased(AEVK_LBUTTON))
	{
		if (ammo > 0) {
			ammo--;
		}
		release_hook();
	}

}



//For interracting with the main menu
void Input_menu_mode()
{
	AEInputUpdate();

	int cursor_x;
	int cursor_y;

	//temporary input, will need to translate as the camera moves ....
	AEInputGetCursorPosition(&cursor_x, &cursor_y);

	translate_cursor(cursor_x, cursor_y);

	AEVec2 mouse_pos{ static_cast <float>(cursor_x), static_cast <float>(cursor_y) };
	//TODO create AABB for button-> dont put it here, can just intialse it with the AABB as the button is static. 

	for (Button& button : buttons)
	{
		if (CollisionIntersection_PointRect(mouse_pos, button.aabb) && AEInputCheckTriggered(AEVK_LBUTTON) || AEInputCheckReleased(AEVK_RETURN))
		{
			if (button.type == TITLE) {
				next = GS_LEVEL1;
			}
			//TODO is what happens after you click -> e.g changing to different screen or etc
		}


	}
}
