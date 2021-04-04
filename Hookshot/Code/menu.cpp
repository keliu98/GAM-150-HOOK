#include "pch.h"

AEGfxVertexList* button = 0;
AEGfxVertexList* text = 0;
AEGfxTexture * pTex1; 

//TODO~!!! FREE MEMORY AND CREATE BUTTONS ARRAY, pointer to a list of buttons

void menu_Load() {
	load_render();//change this during merge
	load_button_texture();//change this during merge
}

void menu_Initialize()
{	

	//change this during merge
	AEVec2 pos{ 0.0f, 0.0f };
	//Creatinf level 1 button

	create_button(GS_LEVEL1, "Start Game", {-0.2,-0.2}, 200.0f, 45.0f);
	create_button(GS_LEVEL_SELECT, "Select Level", { -0.2,-0.35 }, 200.0f, 45.0f);
	create_button(GS_CREDITS, "Credits", { -0.2,-0.50 }, 200.0f, 45.0f);
	create_button(GS_QUIT, "Quit Game", {-0.2,-0.65 }, 200.0f, 45.0f);

	//change this during merge
	AEGfxSetCamPosition(0, 0); // reset cam pos
	//AEVec2 pos2{ -300.0f, -300.0f };
	//create_button(TITLE, pos2, 600.0f);//change this during merge
	
}

void menu_Update() {
	Input_menu_mode();
	UpdateButton();
	//std::cout << buttons[0].pos.x << " " << buttons[0].pos.y << "\n";
	//std::cout << buttons[0].aabb.min.x << " " << buttons[0].aabb.min.y << "\n";
}

void menu_Draw() {
	update_render_buttons();//change this during merge
}

void menu_Free() {

}

void menu_Unload() {
	unload_render();//change this during merge

	
}