#pragma once

#include "pch.h"

struct Render
{
	AEVec2 pos;
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTexture;

	float dir;
	float x_scale;
	float y_scale;

	AEMtx33 transform;
};

AEGfxVertexList* load_mesh()
{

	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5, -0.5, 0x00FF00FF, 0.0f, 1.0f,
		0.5, -0.5, 0x00FFFF00, 1.0f, 1.0f,
		-0.5, 0.5, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5, -0.5, 0x00FFFFFF, 1.0f, 1.0f,
		0.5, 0.5, 0x00FFFFFF, 1.0f, 0.0f,
		-0.5, 0.5, 0x00FFFFFF, 0.0f, 0.0f);


	AEGfxVertexList* pMesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh, "Failed to create mesh 1!!");

	return pMesh;
}

AEGfxTexture* load_texture(const char* image)
{

	AEGfxTexture* pTex1st = AEGfxTextureLoad(image);
	AE_ASSERT_MESG(pTex1st, "Failed to create texture1!!");
	return pTex1st;
}

void update_render()
{
	Render render;
	//Drawing character
	draw_render(render);
}


void draw_render(Render &render)
{

	AEMtx33	trans, scale, rot;

	//Scale it by the length of the hook
	AEMtx33Scale(&scale, render.x_scale, render.y_scale);
	// Compute the translation matrix
	AEMtx33Trans(&trans, render.pos.x, render.pos.y);
	//Rotate it by the angle hooked
	AEMtx33Rot(&rot, render.dir);

	AEMtx33Concat(&hook->transform, &rot, &scale);
	AEMtx33Concat(&hook->transform, &trans, &hook->transform);

	// Drawing object  - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);	// set to texture
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set texture
	AEGfxTextureSet(render.pTexture, 0.0f, 0.0f);		// Same object, different texture
	// Draw the mesh
	AEGfxMeshDraw(render.pMesh, AE_GFX_MDM_TRIANGLES);

}

void free_render(AEGfxVertexList* pMesh1, AEGfxTexture* pTex1)
{
	AEGfxTextureUnload(pTex1);
	AEGfxMeshFree(pMesh1);

}