#include "pch.h"

int guidePage;

//TODO~!!! FREE MEMORY AND CREATE BUTTONS ARRAY, pointer to a list of buttons

void menu_Load() {
	load_render();//change this during merge
	load_button_texture();//change this during merge
	load_guide_texture();
	music_Load();
	load_credits_render();
	load_bg_render();
}

void menu_Initialize()
{	
	guidePage = 0;
	display_credits = false;
	display_tutorial = false;

	music_Initialize("../Music/EVERYBODYS DANCING - WorldMusic MSCLAT1_06.wav");

	AEGfxSetCamPosition(0, 0); // reset cam pos

	create_button(GS_LEVEL1, "Start Game", { -0.2f,-0.10f }, 200.0f, 45.0f);
	create_button(LEVELSELECT, "Select Level", { -0.2f,-0.25f }, 200.0f, 45.0f);
	create_button(TUTORIAL, "Tutorial", { -0.2f,-0.40f }, 200.0f, 45.0f);

	create_button(OPTIONS, "Options", { -0.2f,-0.55f }, 200.0f, 45.0f);
	create_button(CREDITS, "Credits", { -0.2f,-0.70f }, 200.0f, 45.0f);

	create_button(GS_QUIT, "Quit Game", { -0.2f,-0.85f }, 200.0f, 45.0f);
	
}

void menu_Update() {
	Input_menu_mode();
	UpdateButton();
}

void menu_Draw() {
	update_render_bg();

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

	update_render_buttons();//change this during merge
}

void menu_Free() {
	music_Free();
	free_button();
}

void menu_Unload() {
	unload_render();//change this during merge
}
