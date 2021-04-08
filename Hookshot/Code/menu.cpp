#include "pch.h"

int guidePage;

void menu_Load() {
	load_render();//change this during merge
	load_button_texture();//change this during merge
	load_guide_texture();
	load_credits_render();
	load_menubg_render();

	music_Load("../Music/NEW YEARS - Holidays MSCHOL2_54.wav");
}

void menu_Initialize()
{	
	guidePage = 0;
	display_credits = false;
	display_tutorial = false;
	confirm_state = false;

	if (!sound_mute)
	{
		music_Initialize();
	}

	AEGfxSetCamPosition(0, 0); // reset cam pos

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
	update_render_menubg();

	if (display_credits == true)
		update_render_credits();
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

	update_render_buttons();
}

void menu_Free() {
	music_Free();
	free_button();
}

void menu_Unload() {
	unload_render();//change this during merge
	music_Unload();
}
