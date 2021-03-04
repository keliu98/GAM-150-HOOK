#include "pch.h"

AEGfxVertexList* button = 0;

void menu_Load() {
	AEGfxMeshStart();

	AEGfxTriAdd(
		-2.5f, 0.5f, 0x0F52BA, 0.0f, 0.0f,
		-2.5f, -0.5f, 0x0F52BA, 0.0f, 0.0f,
		2.5f, 0.5f, 0x0F52BA, 0.0f, 0.0f);

	AEGfxTriAdd(
		2.5f, -0.5f, 0x0F52BA, 0.0f, 0.0f,
		-2.5f, -0.5f, 0x0F52BA, 0.0f, 0.0f,
		2.5f, 0.5f, 0x0F52BA, 0.0f, 0.0f);

	button = AEGfxMeshEnd();
	AE_ASSERT_MESG(button, "Failed to create button1!!");
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
	AEMtx33	trans, scale, rot;

	// Compute the scaling matrix
	AEMtx33Scale(&scale, button_1->scale, button_1->scale);

	// Compute the translation matrix
	AEMtx33Trans(&trans, button_1->pos.x, button_1->pos.y);

	AEMtx33Concat(&button_1->transform, &trans, &scale);

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTransform(button_1->transform.m);
	AEGfxMeshDraw(button, AE_GFX_MDM_TRIANGLES);

	if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
		next = GS_QUIT;




}

void menu_Free() {
	
}

void menu_Unload() {
	AEGfxMeshFree(button);
}