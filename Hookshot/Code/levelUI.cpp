#include "levelUI.h"

static char	font_to_use;
bool confirm_state = false;
const int YES = 100;
const int NO = 101;

void PrintText(char* message, int type, AEVec2 position)	// italic or norm
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	if (type == NORMAL)
		font_to_use = font;
	else
		font_to_use = font_italic;

	AEGfxPrint(font_to_use, message, position.x, position.y, 1.0f, 1.f, 1.f, 1.f);
}

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

void UpdatePauseMenu()
{
	//If true create the buttons 
	if (PAUSE == true && buttons.empty())
	{
		//Buttons works for display now need to make it so that when it enter pause mode the input is based on the menu input and not game input
		create_button(GS_RESTART, "Restart Game", { -0.2,-0.2 }, 200.0f, 45.0f);
	}
	else if (PAUSE == false && !buttons.empty())
	{
		buttons.clear();
	}
}

void switchbuttonstate(int state)
{
	switch (state)
	{
	case GS_LEVEL1:
		next = GS_LEVEL1;
		break;

	case GS_RESTART:
		next = GS_RESTART;
		break;

	case GS_QUIT:
		if (confirm_state == false)
		{
			create_button(YES, "Yes", { -0.5f, 0.0f }, 125.0f, 45.0f);
			create_button(NO, "No", { 0.2f, 0.0f }, 125.0f, 45.0f);
			confirm_state = true;
		}
		break;

	case GS_CREDITS:
		next = GS_RESTART;
		break;

	case GS_INSTRUCTION:
		next = GS_INSTRUCTION;
		break;

	case GS_LEVEL_SELECT:
		next = GS_LEVEL_SELECT;
		break;

	case YES:
		next = GS_QUIT;
		break;

	case NO:
		confirm_state = false;
		buttons.erase(buttons.end() - 1);
		buttons.erase(buttons.end() - 1);
		break;

	}//End of switch case
}
