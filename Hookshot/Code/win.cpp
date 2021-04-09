/*!*************************************************************************
****
\file win.cpp
\authors: Tan Wei Wen
		  Egi Tan
		  Liu Ke
		  Yong Hui

\par DP email:  t.weiwen@digipen.edu

\par Course: CSD 1450
\par Project: Software Engineering Project 2
\date 050421


\brief
  This source file contains the implementation for the win state
****************************************************************************
***/

#include "pch.h"

void win_Load()
{
	music_Load("../Music/NEW YEARS - Holidays MSCHOL2_54.wav");

	//loading texture etc
	load_render();

	//load bg
	load_bg_render();

	// load buttons texture
	load_button_texture();

	//Creates a back button
	create_button(GS_MENU, "Return Menu", { -0.2f, -BUTTONSPACE_Y * 3 }, 200.0f, 45.0f);
}

void win_Initialize()
{
	//Initalise Music
	music_Initialize();
}

void win_Update()
{
	//Handling input
	AEInputUpdate();
	Input_menu_mode();

	//Updates the button interaction
	UpdateButton();
}

void win_Draw()
{
	static char text[100];
	memset(text, 0, 100 * sizeof(char));

	update_render_bg();
	update_render_buttons();

	sprintf_s(text, "Congraturation");
	PrintText(text, NORMAL, { -0.25, 0.2f });
	sprintf_s(text, "You Found the Treasure!!");
	PrintText(text, NORMAL, { -0.45, 0.0f });
	sprintf_s(text, "Winner is you");
	PrintText(text, NORMAL, { -0.25, -0.2f });
}

// Called if change state, for everything including reset
void win_Free()
{
	music_Free();
	free_button();
}

//  Called if change state and State is NOT reset. ie Change levels. Do not unload if reseting.
void win_Unload()
{
	music_Unload();
	unload_render();
}