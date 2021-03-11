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
	create_button(TITLE, pos, 600.0f);//change this during merge
	
}

void menu_Update() {
	AEInputUpdate();
	Input_menu_mode();
}

void menu_Draw() {
	
	update_render_buttons();//change this during merge



}

void menu_Free() {

}

void menu_Unload() {
	unload_render();//change this during merge

	
}