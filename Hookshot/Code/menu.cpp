#include "pch.h"

AEGfxVertexList* button = 0;
AEGfxVertexList* text = 0;
AEGfxTexture * pTex1; 

//TODO~!!! FREE MEMORY AND CREATE BUTTONS ARRAY, pointer to a list of buttons

void menu_Load() {
	AEGfxMeshStart();


	// This shape has 2 triangles
	AEGfxTriAdd(
		-300.0f, -300.0f, 0x00FF00FF, 0.0f, 1.0f,
		300.0f, -300.0f, 0x00FFFF00, 1.0f, 1.0f,
		-300.0f, 300.0f, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		300.0f, -300.0f, 0x00FFFFFF, 1.0f, 1.0f,
		300.0f,  300.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-300.0f, 300.0f, 0x00FFFFFF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh2

	button = AEGfxMeshEnd();

	
	AE_ASSERT_MESG(button, "Failed to create button1!!");

	pTex1 = AEGfxTextureLoad("Title.png");
	AE_ASSERT_MESG(pTex1, "Failed to create texture1!!");

}

void menu_Initialize()
{
	button_1 = create_button();

}

void menu_Update() {
	AEInputUpdate();
	if (AEInputCheckTriggered(AEVK_RETURN))
		next = GS_LEVEL1;
	
}

void menu_Draw() {
	

	// Drawing object 2 - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	// Set position for object 2
	AEGfxSetPosition(0.0f, 0.0f);
	
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set texture
	AEGfxTextureSet(pTex1, 0.0f, 0.0f);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(button, AE_GFX_MDM_TRIANGLES);



}

void menu_Free() {

}

void menu_Unload() {
	AEGfxMeshFree(button);
	AEGfxTextureUnload(pTex1);

	delete[] button_1;
}