#pragma once
#pragma once

#include "AEEngine.h"
#include "testrender.h"

GameObj load_render(const char* image) 
{

	AEGfxMeshStart();

	// 1 triangle at a time
	// X, Y, Color, texU, texV

	AEGfxTriAdd(
		-50.0f, -50.0f, 0xFFFF0000, 0.0f, 0.0f,
		35.5f, 00.0f, 0xFFFF0000, 0.0f, 0.0f,
		-50.0f, 50.0f, 0xFFFF0000, 0.0f, 0.0f);

	AEGfxTriAdd(
		-105.5f, -105.5f, 0x0000FF, 0.0f, 0.0f,
		-80.5f, 80.0f, 0x0000FF, 0.0f, 0.0f,
		-40.5f, 20.5f, 0x0000FF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh1

	AEGfxVertexList* pMesh1 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh1, "Failed to create mesh 1!!");

	AEGfxTexture* pTex1 = AEGfxTextureLoad(image);
	AE_ASSERT_MESG(pTex1, "Failed to create texture1!!");

	GameObj item = { pMesh1, pTex1 };
	return item;
}

void draw_render1(AEVec2 Position, AEGfxVertexList* pMesh1, AEGfxTexture* pTex1)
{
	// Drawing object  - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);	// set to texture
	// Set position for object 2
	AEGfxSetPosition(Position.x, Position.y);
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set texture
	AEGfxTextureSet(pTex1, 0.0f, 0.0f);		// Same object, different texture
	// Draw the mesh
	AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);

}

void free_render(AEGfxVertexList* pMesh1, AEGfxTexture* pTex1)
{
	AEGfxTextureUnload(pTex1);
	AEGfxMeshFree(pMesh1);
}



