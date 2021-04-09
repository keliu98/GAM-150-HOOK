/*!*************************************************************************
****
\file menu.cpp
\par Project: Hookshot
\authors: Tan Wei Wen (85%)
		  Egi Tan (10%)
		  Yong Hui (5%)

\par DP email:  t.weiwen@digipen.edu
                egi.tan@digipen.edu
				l.yonghui@digipen.edu

\par Course: CSD 1450
\date 050421

\brief
This file contains the implementation to for the menu state of the game. Calls
all the necessary functions to display and interact with the menu.

\par Copyright: All content � 2021 Digipen Institute of Technology Singapore. All
				rights reserved.

****************************************************************************
***/

#include "pch.h"

//For storing the page of the tutorial. Extern Variable.
int guidePage;
int creditsPage;

void menu_Load() {//call the necesarry load funnction
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

	create_button(GS_LEVEL1, "Start Game", { -0.2f,-0.0f }, 200.0f, 45.0f);//create start button
	create_button(LEVELSELECT, "Select Level", { -0.2f, -BUTTONSPACE_Y }, 200.0f, 45.0f);// create level selection button
	create_button(TUTORIAL, "Tutorial", { -0.2f, -BUTTONSPACE_Y * 2 }, 200.0f, 45.0f);// create tutorial button

	create_button(OPTIONS, "Options", { -0.2f, -BUTTONSPACE_Y * 3 }, 200.0f, 45.0f);//create option button
	create_button(CREDITS, "Credits", { -0.2f, -BUTTONSPACE_Y * 4 }, 200.0f, 45.0f);//create credit button

	create_button(GS_QUIT, "Quit Game", { -0.2f, -BUTTONSPACE_Y * 5 }, 200.0f, 45.0f);//create quit button
	
}

void menu_Update() {

	//Handling input
	AEInputUpdate();// allow input to be read
	Input_menu_mode();//call menu input function

	//Updating buttons position and translating
	UpdateButton();
}

void menu_Draw() {

	//Draw menu bg
	update_render_menubg(); //update and display thr backgorund

	//Draw tutorial if true
	if (display_tutorial == true)
	{
		switch (guidePage)
		{
			case 0:
				update_render_guide(400.0f, -270.0f);//display page 1
				break;
			case 1:
				update_render_guide(-400.0f, -270.0f);//display page 2
				break;
			case 2:
				update_render_guide(400.0f, 250.0f);//display page 3
				break; 
			case 3:
				update_render_guide(-400.0f, 250.0f);//display page 4
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
	music_Free();//free music
	free_button();//free button
}

void menu_Unload() {
	unload_render();//unload rendered object
	music_Unload();
}
