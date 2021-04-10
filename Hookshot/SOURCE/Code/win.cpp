/*!*************************************************************************
****
\file win.cpp
\par Project: Hookshot
\authors: Tan Wei Wen (100%)

\par DP email:  t.weiwen@digipen.edu

\par Course: CSD 1450
\date 050421

\brief
This file contains the implementation for the win state of the game. Displays the 
game win screen.

\par Copyright: All content ©2021 Digipen Institute of Technology Singapore. All
				rights reserved.

****************************************************************************
***/

#include "pch.h"

void win_Load()
{
	//Load Music
	music_Load("../Music/NEW YEARS - Holidays MSCHOL2_54.wav");

	//loading texture etc
	load_render();

	//load bg
	load_bg_render();

	//load credits
	load_credits_render();

	// load buttons texture
	load_button_texture();

	//Creates a back button
	create_button(CREDITS, "Credits", { -0.2f, -BUTTONSPACE_Y * 3 }, 200.0f, 45.0f);
}

void win_Initialize()
{
	//Initalise Music
	music_Initialize();

	//Reset camera position
	camera_init({ 0,0 });
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
	if (display_credits == false)
	{
		update_render_bg();

		sprintf_s(text, "Congraturation");
		PrintText(text, NORMAL, { -0.25f, 0.2f });
		sprintf_s(text, "You Found the Treasure!!");
		PrintText(text, NORMAL, { -0.45f, 0.0f });
		sprintf_s(text, "Winner is you");
		PrintText(text, NORMAL, { -0.25f, -0.2f });
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

	update_render_buttons();
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