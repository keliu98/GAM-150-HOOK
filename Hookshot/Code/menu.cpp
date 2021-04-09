/*!*************************************************************************
****
\file Menu.cpp
\authors: Tan Wei Wen
		  Yong Hui

\par DP email:  t.weiwen@digipen.edu
				l.yonghui@digipen.edu

\par Course: CSD 1450
\par Project: Software Engineering Project 2
\date 020221


\brief
  This source file contains the implementation for all the menu
  functions.
****************************************************************************
***/


#include "pch.h"

int guidePage;

void menu_Load() {//call the necesarry load funnction
	load_render();
	load_button_texture();
	load_guide_texture();
	load_credits_render();
	load_menubg_render();

	music_Load("../Music/NEW YEARS - Holidays MSCHOL2_54.wav");//load music
}

void menu_Initialize()
{	//initialized the variable
	guidePage = 0;
	display_credits = false;
	display_tutorial = false;
	confirm_state = false;

	if (!sound_mute)
	{
		music_Initialize();//as long as sound is not muted, initialized music
	}

	AEGfxSetCamPosition(0, 0); // reset cam pos

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
	update_render_menubg();//update and display thr backgorund

	if (display_credits == true)//if credit is set to true
		update_render_credits();//display credit
	if (display_tutorial == true)//if tutorial is true 
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

	update_render_buttons();//dusplay button
}

void menu_Free() {
	music_Free();//free music
	free_button();//free button
}

void menu_Unload() {
	unload_render();//unload rendered object
	music_Unload();
}
