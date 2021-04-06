#include "pch.h"

int guidePage;

//TODO~!!! FREE MEMORY AND CREATE BUTTONS ARRAY, pointer to a list of buttons

void menu_Load() {
	load_render();//change this during merge
	load_button_texture();//change this during merge
	load_guide_texture();
	music_Load();
	load_credits_render();
	load_tutorial_render();


}

void menu_Initialize()
{	
	guidePage = 0;
	display_credits = false;
	display_tutorial = false;

	music_Initialize("../Music/bensound-ukulele.mp3");

	AEGfxSetCamPosition(0, 0); // reset cam pos

	create_button(GS_LEVEL1, "Start Game", { -0.2,-0.10 }, 200.0f, 45.0f);
	create_button(LEVELSELECT, "Select Level", { -0.2,-0.25 }, 200.0f, 45.0f);
	create_button(TUTORIAL, "Tutorial", { -0.2,-0.40 }, 200.0f, 45.0f);

	create_button(OPTIONS, "Options", { -0.2,-0.55 }, 200.0f, 45.0f);
	create_button(CREDITS, "Credits", { -0.2,-0.70 }, 200.0f, 45.0f);

	create_button(GS_QUIT, "Quit Game", { -0.2,-0.85 }, 200.0f, 45.0f);
	
}

void menu_Update() {
	Input_menu_mode();
	UpdateButton();
}

void menu_Draw() {
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
				update_render_guide(400.0f, -270.0f);
				break;
			case 3:
				update_render_guide(-400.0f, -270.0f);
				break;
		}
	}
	update_render_buttons();//change this during merge

	static char text[100];
	memset(text, 0, 100 * sizeof(char));

	sprintf_s(text, "Hookshot\n");
	PrintText(text, NORMAL, { -0.15f, 0.2f });

}

void menu_Free() {
	music_Free();
	free_button();
}

void menu_Unload() {
	unload_render();//change this during merge
}
