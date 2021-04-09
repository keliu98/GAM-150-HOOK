/*!*************************************************************************
****
\file menu.cpp
\par Project: Hookshot
\authors: Tan Wei Wen (90%)
		  Egi Tan (10%)

\par DP email:  t.weiwen@digipen.edu
                egi.tan@digipen.edu

\par Course: CSD 1450
\date 050421

\brief
This file contains the implementation to for the menu state of the game. Calls
all the necessary functions to display and interact with the menu.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. All
				rights reserved.

****************************************************************************
***/

#include "pch.h"

//For storing the page of the tutorial. Extern Variable.
int guidePage;
int creditsPage;

void menu_Load() {

	//Loading render
	load_render();
	load_button_texture();
	load_guide_texture();
	load_credits_render();
	load_menubg_render();

	//Loading music
	music_Load("../Music/NEW YEARS - Holidays MSCHOL2_54.wav");
}

void menu_Initialize()
{	
	//Intialising variables for displaying.
	creditsPage = 0;
	guidePage = 0;
	display_credits = false;
	display_tutorial = false;
	confirm_state = false;

	//Intialise music
	music_Initialize();

	//Reset camera position
	camera_init({ 0,0 });

	//Creating buttons needed for the menu
	create_button(GS_LEVEL1, "Start Game", { -0.2f,-0.0f }, 200.0f, 45.0f);
	create_button(LEVELSELECT, "Select Level", { -0.2f, -BUTTONSPACE_Y }, 200.0f, 45.0f);
	create_button(TUTORIAL, "Tutorial", { -0.2f, -BUTTONSPACE_Y * 2 }, 200.0f, 45.0f);
	create_button(OPTIONS, "Options", { -0.2f, -BUTTONSPACE_Y * 3 }, 200.0f, 45.0f);
	create_button(CREDITS, "Credits", { -0.2f, -BUTTONSPACE_Y * 4 }, 200.0f, 45.0f);
	create_button(GS_QUIT, "Quit Game", { -0.2f, -BUTTONSPACE_Y * 5 }, 200.0f, 45.0f);
	
}

void menu_Update() {

	//Handling input
	AEInputUpdate();
	Input_menu_mode();

	//Updating buttons position and translating
	UpdateButton();
}

void menu_Draw() {

	//Draw menu bg
	update_render_menubg();

	//Draw tutorial if true
	if (display_tutorial == true)
	{
		switch (guidePage)
		{
			case 0:
				update_render_guide(400.0f, -270.0f);
				break;
			case 1:
				update_render_guide(-400.0f, -270.0f);
				break;
			case 2:
				update_render_guide(400.0f, 250.0f);
				break;
			case 3:
				update_render_guide(-400.0f, 250.0f);
				break;
		}
	}

	//Draw credits if true
	if (display_credits == true)
	{
		switch (creditsPage)
		{
		case 0:
			update_render_credits(0.0f, -250.0f);
			break;
		case 1:
			update_render_credits(0.0f, 250.0f);
			break;
		}
	}

	//Draw buttons
	update_render_buttons();
}

void menu_Free() {
	music_Free();
	free_button();
}

void menu_Unload() {
	unload_render();
	music_Unload();
}
