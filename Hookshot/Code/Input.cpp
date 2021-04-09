/*!*************************************************************************
****
\file Input.cpp
\authors: Yong Hui

\par DP email: l.yonghui@digipen.edu

\par Course: CSD 1450
\par Project: Software Engineering Project 2
\date 020221


\brief
  This source file contains the implementation for all the Input function.
****************************************************************************
***/


#include"pch.h"
#include"collision.h"

bool PAUSE = false; //set pause to off

void skip_intro()
{
	AEInputUpdate();

	if (AEInputCheckReleased(AEVK_LBUTTON)) //if left click is clicked and released
	{
		next = GS_MENU;//move to menu
	}
}

void Input_g_mode() { // Game mode configuration

	float CHARACTER_ACCEL_HORI = 500.0f;// set speed to 500

	if (AEInputCheckTriggered(AEVK_ESCAPE))
		PAUSE = !PAUSE;//if escape is pressed 

	if (PAUSE == true)
	{
		release_hook();// unhook the hook
		Input_menu_mode();//switch to menu mode
		return;
	}
	
	//Keyboard
	if (character->grid_collision_flag != COLLISION_LEFT && AEInputCheckCurr(AEVK_A))//if 'A' buttom is pressed, move left
		// || (hook->hook_state == tethered && Flag != COLLISION_BOTTOM)
	{
		AEVec2 dir = { -1.0f, 0.0f };// set direction to move leftward
		set_accel_to_vel(character->velocity, dir, CHARACTER_ACCEL_HORI);//apply speed to direction
	}

	if (character->grid_collision_flag != COLLISION_RIGHT && AEInputCheckCurr(AEVK_D))//if 'D' buttom is pressed, move right
	{
		AEVec2 dir = { 1.0f, 0.0f };//set direction for character to move rightward
		set_accel_to_vel(character->velocity, dir, CHARACTER_ACCEL_HORI);//apply speed to direction
	}

	if (character->grid_collision_flag != COLLISION_TOP && (AEInputCheckTriggered(AEVK_W) || //if 'w' or 'space; button is pressed, jump and hook is not fired
		AEInputCheckTriggered(AEVK_SPACE)) && hook->flag == false)
	{
		if (character->char_state != jumping)//as long as character is not jumping (jump limiter)
		{
			character->velocity.y += CHAR_HEIGHT_VEL;//make player jump
			character->char_state = jumping;//set state to jump
		}
	}

	if (AEInputCheckCurr(AEVK_M))//debug code
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

	if (AEInputCheckTriggered(AEVK_LBUTTON) && ammo > 0) {// as long as the number of shot is not zero and the left button is pressed
		ammoD--;//reduce ammo display count
		// std::cout << ammo;
	}

	if (character->counter < 90 && AEInputCheckCurr(AEVK_LBUTTON) && ammo > 0)// if there is still ammo(internal) 
	{
		fire_hook(cursor_x, cursor_y);//fire hook
	}

	if (AEInputCheckReleased(AEVK_LBUTTON))//when left click is release
	{
		if (ammo > 0) {
			ammo--;//reduce the internal ammo count
		}
		release_hook();//release hook
	}

}



//For interracting with the main menu
void Input_menu_mode()
{
	int cursor_x;
	int cursor_y;

	//temporary input, will need to translate as the camera moves ....
	AEInputGetCursorPosition(&cursor_x, &cursor_y);//read cursor position

	translate_cursor(cursor_x, cursor_y);//translate the position
	//std::cout << cursor_x << " " << cursor_y << "\n";
	AEVec2 mouse_pos{ static_cast <float>(cursor_x), static_cast <float>(cursor_y) };//store the position into AEvec

	//TODO create AABB for button-> dont put it here, can just intialse it with the AABB as the button is static. 

	for (Button& button : buttons)
	{
		if (CollisionIntersection_PointRect(mouse_pos, button.aabb))//check for bounding box
		{
			button.highlight = true;//highlight the button

			if (AEInputCheckTriggered(AEVK_LBUTTON))//if left mouse button is oress
			{
				switchbuttonstate(button.state);//switch the button state
				
			}
		}
		else
			button.highlight = false;//unhighlight the button
	}

	// -------------------------------------------------

	// -------------------------------GUIDES-----------------------------

	// while guide is open check for next or previous
	if (display_tutorial)
	{
		// next
		if (guidePage >= 0 && guidePage < 3 && AEInputCheckReleased(AEVK_D)) // when D is pressed 
		{
			++guidePage; // move to the next page
			//std::cout << guidePage << std::endl;
		}
		// previous
		if (guidePage > 0 && guidePage < 4 && AEInputCheckReleased(AEVK_A))//when A is pressed
		{
			--guidePage; //move to the previous page
			//std::cout << guidePage << std::endl;
		}
	}
}



