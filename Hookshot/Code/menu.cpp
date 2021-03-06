#include "pch.h"

AEGfxVertexList* button = 0;
AEGfxVertexList* text = 0;
AEGfxTexture * pTex1; 
bool openGuide;
int guidePage;

//TODO~!!! FREE MEMORY AND CREATE BUTTONS ARRAY, pointer to a list of buttons

void menu_Load() {
	load_render();//change this during merge
	load_button_texture();//change this during merge
	load_guide_texture();
	music_Load();

	create_button(GS_LEVEL1, "Start Game", { -0.2f,-0.2f }, 200.0f, 45.0f);
	create_button(GS_LEVEL_SELECT, "Select Level", { -0.2f,-0.35f }, 200.0f, 45.0f);
	create_button(GS_INSTRUCTION, "Instructions", { -0.2f,-0.50f }, 200.0f, 45.0f);
	create_button(GS_CREDITS, "Credits", { -0.2f,-0.65f }, 200.0f, 45.0f);
	create_button(GS_QUIT, "Quit Game", { -0.2f,-0.80f }, 200.0f, 45.0f);
}

void menu_Initialize()
{	
	guidePage = 0;
	openGuide = false;
	//change this during merge
	AEVec2 pos{ 0.0f, 0.0f };


	//change this during merge
	AEGfxSetCamPosition(0, 0); // reset cam pos
	//AEVec2 pos2{ -300.0f, -300.0f };
	//create_button(TITLE, pos2, 600.0f);//change this during merge
	music_Initialize("../Music/bensound-ukulele.mp3");
}

void menu_Update() {
	Input_menu_mode();
	UpdateButton();
}

void menu_Draw() {

	update_render_buttons();//change this during merge

	static char text[100];
	memset(text, 0, 100 * sizeof(char));

	sprintf_s(text, "Hookshot\n");
	PrintText(text, NORMAL, { -0.15f, 0.2f });

	// PrintText(text, NORMAL, { -0.42f, 0.0f });
	// sprintf_s(text, "PRESS 1 for Level 1\n");
	// PrintText(text, NORMAL, { -0.42f, -0.15f });
	// sprintf_s(text, "PRESS 2 for Level 2\n");
	// PrintText(text, NORMAL, { -0.42f, -0.25f });
	// sprintf_s(text, "PRESS 3 for Level 3\n");
	// PrintText(text, NORMAL, { -0.42f, -0.35f });
	// sprintf_s(text, "PRESS I FOR INSTRUCTIONS\n");

	// open guide
	if (openGuide)
	{
		switch (guidePage)
		{
			case 0:
				update_render_guide(400.0f, -300.0f);
				break;
			case 1:
				update_render_guide(-400.0f, -300.0f);
				break;
			case 2:
				update_render_guide(400.0f, 300.0f);
				break;
			case 3:
				update_render_guide(-400.0f, 300.0f);
				break;
		}
	}

}

void menu_Free() {
	music_Free();
}

void menu_Unload() {
	unload_render();//change this during merge
	free_button();
}
