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
}

void menu_Initialize()
{	
	guidePage = 0;
	openGuide = false;
	//change this during merge
	AEVec2 pos{ 0.0f, 0.0f };
	//Creatinf level 1 button

	create_button(GS_LEVEL1, "hi testing testing testing", {0,0}, 100.0f, 30.0f);
	//change this during merge
	AEGfxSetCamPosition(0, 0); // reset cam pos
	//AEVec2 pos2{ -300.0f, -300.0f };
	//create_button(TITLE, pos2, 600.0f);//change this during merge
	
}

void menu_Update() {
	Input_menu_mode();
	//std::cout << buttons[0].pos.x << " " << buttons[0].pos.y << "\n";
	//std::cout << buttons[0].aabb.min.x << " " << buttons[0].aabb.min.y << "\n";
}

void menu_Draw() {

	update_render_buttons();//change this during merge

	static char text[100];
	memset(text, 0, 100 * sizeof(char));
	sprintf_s(text, "PRESS I FOR INSTRUCTIONS\n");
	PrintText(text, NORMAL, { -0.42f, -0.35f });

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

}

void menu_Unload() {
	unload_render();//change this during merge
}
