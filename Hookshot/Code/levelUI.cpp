/*!*************************************************************************
****
\file levelUI.cpp
\par Project: Hookshot
\authors: Tan Wei Wen (90%)
		  Egi Tan (10%)

\par DP email:  t.weiwen@digipen.edu
                egi.tan@digipen.edu

\par Course: CSD 1450
\date 050421

\brief
This file contains the implementation for the UI of the game. For example
creating buttons and printing text on to the screen.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. All
				rights reserved.

****************************************************************************
***/

#include "levelUI.h"

//To store font.
static char	font_to_use;

//Booleans used for checking
bool confirm_state = false;
bool full_screen = true;
bool sound_mute = false;

//To check if there is a need to display credits and tutorial
bool display_credits = false;
bool display_tutorial = false;

//DEFINES to switch between buttons
const int CONFIRM_QUIT = 100;

const int PAUSE_MENU = 92;
const int OPTIONS_INGAME = 93;
const int FULLSCREEN = 94;
const int SOUND = 95;

const int TUTORIAL = 96;
const int LEVELSELECT = 97;
const int CREDITS = 98;
const int OPTIONS = 99;
const int MENU = 91;

//DEFINE to use when creating buttons, makes life easier.
const float BUTTONSPACE_Y = 0.18f;

//Function to print text onto the screen
void PrintText(char* message, int type, AEVec2 position)	// italic or norm
{
	AE_ASSERT_MESG(message, "No message set for print text.");

	if (type == NORMAL)
		font_to_use = font;
	else if (type == ITALIC)
		font_to_use = font_italic;
	else
		font_to_use = smaller_font;

	AEGfxPrint(font_to_use, message, position.x, position.y, 1.0f, 1.f, 1.f, 1.f);
}

//Function to translate buttons so that they can be created based on ratio of the screen.
void UpdateButton()
{
	for (Button& button : buttons)
	{
		//Shifting the button position and AABB based on the ratio to screen width and height rather than actual position
		button.pos_trans.x =  (WINDOW_WIDTH / 2 * button.pos_ratio.x ) + button.scale.x / 2 - 20.0f;
		button.pos_trans.y = (WINDOW_HEIGHT / 2 * button.pos_ratio.y) + 5.0f;

		//Translating base on camera TODO
		translate_UI(button.pos_trans);

		//create AABB
		create_AABB(button.aabb, button.pos_trans, button.scale.x, button.scale.y);
	}
}

//For creating the pause menu.
void UpdatePauseMenu()
{
	//If true create the buttons 
	if (PAUSE == true && buttons.empty())
	{
		//Buttons works for display now need to make it so that when it enter pause mode the input is based on the menu input and not game input
		create_button(GS_RESTART, "Restart Lvl", { -0.2f,-0.0f }, 200.0f, 45.0f);
		create_button(OPTIONS_INGAME, "Options", { -0.2f,-BUTTONSPACE_Y }, 200.0f, 45.0f);
		create_button(GS_MENU, "Return Menu", { -0.2f, -BUTTONSPACE_Y * 2 }, 200.0f, 45.0f);
	}
	else if (PAUSE == false && !buttons.empty())
	{
		buttons.clear();
	}
}

//Function to switch between the different states and actions for each button.
void switchbuttonstate(int state)
{
	switch (state)
	{
	case GS_LEVEL1:
		next = GS_LEVEL1;
		break;

	case GS_LEVEL2:
		next = GS_LEVEL2;
		break;

	case GS_LEVEL3:
		next = GS_LEVEL3;
		break;

	case GS_LEVEL4:
		next = GS_LEVEL4;
		break;

	case GS_LEVEL5:
		next = GS_LEVEL5;
		break;

	case GS_RESTART:
		next = GS_RESTART;
		break;

	case GS_MENU:
		next = GS_MENU;
		break;

	case GS_QUIT:
		if (confirm_state == false)
		{
			create_button(CONFIRM_QUIT, "You Sure ?", { -0.2f, -0.18f * 5 }, 200.0f, 45.0f);
			confirm_state = true;
		}
		break;

	case MENU:
		display_tutorial = false;
		display_credits = false;
		free_button();
		create_button(GS_LEVEL1, "Start Game", { -0.2f,-0.0f }, 200.0f, 45.0f);//create start button
		create_button(LEVELSELECT, "Select Level", { -0.2f, -BUTTONSPACE_Y }, 200.0f, 45.0f);// create level selection button
		create_button(TUTORIAL, "How to play", { -0.2f, -BUTTONSPACE_Y * 2 }, 200.0f, 45.0f);// create tutorial button

		create_button(OPTIONS, "Options", { -0.2f, -BUTTONSPACE_Y * 3 }, 200.0f, 45.0f);//create option button
		create_button(CREDITS, "Credits", { -0.2f, -BUTTONSPACE_Y * 4 }, 200.0f, 45.0f);//create credit button

		create_button(GS_QUIT, "Quit Game", { -0.2f, -BUTTONSPACE_Y * 5 }, 200.0f, 45.0f);//create quit button
		break;

	case CONFIRM_QUIT:
		if (confirm_state == true)
		{
			next = GS_QUIT;
			confirm_state = false;
		}
		break;

	case LEVELSELECT:
		free_button();
		create_button(GS_LEVEL1, "Level 1", { -0.2f, 0.0f }, 200.0f, 45.0f);
		create_button(GS_LEVEL2, "Level 2", { -0.2f,-BUTTONSPACE_Y}, 200.0f, 45.0f);
		create_button(GS_LEVEL3, "Level 3", { -0.2f,-BUTTONSPACE_Y * 2 }, 200.0f, 45.0f);
		create_button(GS_LEVEL4, "Level 4", { -0.2f,-BUTTONSPACE_Y * 3 }, 200.0f, 45.0f);
		create_button(GS_LEVEL5, "Level 5", { -0.2f,-BUTTONSPACE_Y * 4 }, 200.0f, 45.0f);

		create_button(MENU, "Back", { 0.4f,-0.80f }, 100.0f, 45.0f);
		break;

	case TUTORIAL:
		free_button();
		display_tutorial = true;
		create_button(MENU, "Back", { -0.9f, 0.80f }, 100.0f, 45.0f);
		break;

	case CREDITS:
		free_button();
		display_credits = true;
		if (current == GS_MENU)
		{
			create_button(MENU, "Back", { -0.9f, 0.80f }, 100.0f, 45.0f);
		}
		else
			create_button(GS_MENU, "Back", { -0.9f, 0.80f }, 100.0f, 45.0f);
		break;

	case OPTIONS:
		free_button();
		create_button(FULLSCREEN, "Toggle Screen", { -0.25f,0.0f }, 220.0f, 45.0f);
		create_button(SOUND, "Toggle Music", { -0.25f,-BUTTONSPACE_Y}, 220.0f, 45.0f);

		create_button(MENU, "Back", { 0.4f,-0.80f }, 100.0f, 45.0f);
		break;

	case OPTIONS_INGAME:
		free_button();
		create_button(FULLSCREEN, "Toggle Screen", { -0.25f,0.0f }, 220.0f, 45.0f);
		create_button(SOUND, "Toggle Music", { -0.25f,-BUTTONSPACE_Y }, 220.0f, 45.0f);

		create_button(PAUSE_MENU, "Back", { 0.4f,-0.80f }, 100.0f, 45.0f);
		break;

	case PAUSE_MENU:
		free_button();
		create_button(GS_RESTART, "Restart Lvl", { -0.2f,-0.0f }, 200.0f, 45.0f);
		create_button(OPTIONS_INGAME, "Options", { -0.2f,-BUTTONSPACE_Y }, 200.0f, 45.0f);
		create_button(GS_MENU, "Return Menu", { -0.2f, -BUTTONSPACE_Y * 2 }, 200.0f, 45.0f);
		break;

	case FULLSCREEN:
		if (full_screen == true)
		{
			AEToogleFullScreen(false);
			full_screen = false;
		}
		else
		{
			AEToogleFullScreen(true);
			full_screen = true;
		}
		break;

	case SOUND:
		//TODO TURN ON AND OFF SOUND
		if (sound_mute == false)
		{
			music_mute(true);
			sound_mute = true;
		}
		else
		{
			music_mute(false);
			sound_mute = false;
		}


	}//End of switch case
}
