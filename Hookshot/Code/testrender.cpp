#pragma once
#pragma once

#include "pch.h"

AEGfxVertexList* pMesh;
AEGfxVertexList* pMesh4;
AEGfxTexture* pTex1st;
int counter = 0;
AEGfxTexture* pTex2nd;	// loop through every texture

float objtexX = 0, objtexY = 0;

void load_mesh()
{

	AEGfxMeshStart();

	// 1 triangle at a time
	// X, Y, Color, texU, texV
	/**/


	AEGfxTriAdd(
		-25.0f, -25.0f, 0x00FF00FF, 0.0f, 1.0f,
		-25.0f, 25.0f, 0xFFFF0000, 1.0f, 1.0f,
		25.0f, 25.0f, 0xFFFF0000, 0.0f, 0.0f);

	AEGfxTriAdd(
		25.0f, 25.0f, 0xFFFF0000, 1.0f, 1.0f,
		25.0f, -25.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-25.0f, -25.0f, 0x00FFFFFF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh1

	pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh, "Failed to create mesh 1!!");
	std::cout << "meshdraw\n";

	AEGfxVertexList* pMeshLine = pMesh;

}


void load_hookmesh()
{
	AEGfxMeshStart();

	// 2 triangle at a time
	// X, Y, Color, texU, texV

	AEGfxTriAdd(
		-0.5f, 0.5f, 0x00FF00FF, 0.0f, 1.0f,
		-0.5f, -0.5f, 0x00FFFF00, 1.0f, 1.0f,
		0.5f, 0.5f, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x00FFFFFF, 1.0f, 1.0f,
		-0.5f, -0.5f, 0x00FFFFFF, 1.0f, 0.0f,
		0.5f, 0.5f, 0x00FFFFFF, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh1

	pMesh4 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh4, "Failed to create mesh 1!!");
	std::cout << "hookmeshline\n";

	AEGfxVertexList* pMeshLine = pMesh4;


}

void load_texture(const char* image)
{

	 pTex1st = AEGfxTextureLoad("testimageCopy.png");
	AE_ASSERT_MESG(pTex1st, "Failed to create texture1!!");
	std::cout << "texturedraw\n";

	pTex2nd = AEGfxTextureLoad("YellowTexture.png");
	AE_ASSERT_MESG(pTex2nd, "Failed to create texture1!!");
	std::cout << "texturedraw\n";

}


void draw_render1(AEVec2 Position, AEGfxVertexList* pMesh1, AEGfxTexture* pTex1)
{ 
	// Texture offset
	if (AEInputCheckCurr(AEVK_L))
		objtexX -= 0.01f;
	else if (AEInputCheckCurr(AEVK_J))
		objtexX += 0.01f;

	if (AEInputCheckCurr(AEVK_I))
		objtexY += 0.01f;
	else if (AEInputCheckCurr(AEVK_K))
		objtexY -= 0.01f;


	// Drawing object  - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);	// set to texture
	// Set position for object 2
	AEGfxSetPosition(Position.x, Position.y);
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set texture
	AEGfxTextureSet(pTex1st, 0.0f, 0.0f);		// Same object, different texture
	// Draw the mesh
	AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
	// Set Transparency
	AEGfxSetTransparency(1.0f);
	AEGfxTextureSet(pTex1st, objtexX, objtexY);
	++counter;
	if (counter < 120)
		AEGfxTextureSet(pTex1st, objtexX, objtexY);		// Same object, different texture
	else if (counter < 240)
		AEGfxTextureSet(pTex2nd, objtexX, objtexY);		// Same object, different texture
	else
	{
		AEGfxTextureSet(pTex1st, objtexX, objtexY);		// Same object, different texture
		counter = 0;
	}

}

void free_render(AEGfxVertexList* pMesh1, AEGfxTexture* pTex1)
{
	AEGfxTextureUnload(pTex1st);
	AEGfxMeshFree(pMesh);
	AEGfxMeshFree(pMesh4);
	AEGfxTextureUnload(pTex2nd);
}



