#include"pch.h"
#include"collision.h"

bool PAUSE = false;

void skip_intro()
{
	AEInputUpdate();
	fullScreen();

	if (AEInputCheckReleased(AEVK_LBUTTON))
	{
		next = GS_MENU;
	}
}

void Input_g_mode() {

	float CHARACTER_ACCEL_HORI = 500.0f;

	if (AEInputCheckTriggered(AEVK_ESCAPE))
		PAUSE = !PAUSE;

	if (PAUSE == true)
	{
		release_hook();
		Input_menu_mode();
		return;
	}
	
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

	if (AEInputCheckCurr(AEVK_M))
	{
		next = GS_MENU;
	}


	//-----------For firing hook at enemies---------------
	//Mouse Press and position
	int cursor_x;
	int cursor_y;

	//Get Cursor position.
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
	int cursor_x;
	int cursor_y;

	//temporary input, will need to translate as the camera moves ....
	AEInputGetCursorPosition(&cursor_x, &cursor_y);

	translate_cursor(cursor_x, cursor_y);
	//std::cout << cursor_x << " " << cursor_y << "\n";
	AEVec2 mouse_pos{ static_cast <float>(cursor_x), static_cast <float>(cursor_y) };

	//TODO create AABB for button-> dont put it here, can just intialse it with the AABB as the button is static. 

	for (Button& button : buttons)
	{
		if (CollisionIntersection_PointRect(mouse_pos, button.aabb))
		{
			button.highlight = true;

			if (AEInputCheckTriggered(AEVK_LBUTTON))
			{
				switchbuttonstate(button.state);
				
			}
		}
		else
			button.highlight = false;
	}

	// -------------------------------------------------

	// -------------------------------GUIDES-----------------------------

	// while guide is open check for next or previous
	if (display_tutorial)
	{
		// next
		if (guidePage >= 0 && guidePage < 3 && AEInputCheckReleased(AEVK_D))
		{
			++guidePage;
			std::cout << guidePage << std::endl;
		}
		// previous
		if (guidePage > 0 && guidePage < 4 && AEInputCheckReleased(AEVK_A))
		{
			--guidePage;
			std::cout << guidePage << std::endl;
		}
	}
}



