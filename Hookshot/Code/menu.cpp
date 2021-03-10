#include "pch.h"

AEGfxVertexList* button = 0;
AEGfxVertexList* text = 0;
AEGfxTexture * pTex1; 

//TODO~!!! FREE MEMORY AND CREATE BUTTONS ARRAY, pointer to a list of buttons

void menu_Load() {
	load_render();
	load_button_texture();
}

void menu_Initialize()
{
	AEVec2 pos{ 0.0f, 0.0f };
	create_button(TITLE, pos, 600.0f);

}

void menu_Update() {
	AEInputUpdate();
	if (AEInputCheckTriggered(AEVK_RETURN))
		next = GS_LEVEL1;
	
}

void menu_Draw() {
	
	update_render_buttons();



}

void menu_Free() {

}

void menu_Unload() {
	unload_render();

	
}