#include "intro.h"

//Pointer to square mesh
static AEGfxVertexList* logo_mesh;
static AEGfxTexture* logo;
static float transparency;
static bool shown;

void intro_Load()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-1.5, -0.5, 0x00FF00FF, 0.0f, 1.0f,
		1.5, -0.5, 0x00FFFF00, 1.0f, 1.0f,
		-1.5, 0.5, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		1.5, -0.5, 0x00FFFFFF, 1.0f, 1.0f,
		1.5, 0.5, 0x00FFFFFF, 1.0f, 0.0f,
		-1.5, 0.5, 0x00FFFFFF, 0.0f, 0.0f);


	logo_mesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(logo_mesh, "Failed to create logo mesh!!");

	logo = AEGfxTextureLoad("../Images/DigiPen_Singapore_WEB_RED.png");
}

void intro_Initialize()
{
	transparency = 0;
	shown = false;
}

void intro_Update()
{
	skip_intro();

	if (!shown && transparency <= 1)
	{
		transparency += g_dt;
		if (transparency >= 1)
			shown = true;
	}
		
	else
	{
		transparency -= g_dt;
		if (transparency <= 0)
		{
			next = GS_MENU;
		}
	}
		

	// std::cout << transparency << std::endl;
}

void intro_Draw()
{
	AEMtx33	trans, scale, logo_trans;
	// Compute the scalling matrix
	AEMtx33Scale(&scale, 150, 150);
	// Compute the translation matrix
	AEMtx33Trans(&trans, 0, 0);
	//Combining the matrix
	AEMtx33Concat(&logo_trans, &trans, &scale);

	// Drawing object  - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);	// set to texture
		//For the texture to blend into the game.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(transparency);
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set texture
	AEGfxTextureSet(logo, 0.0f, 0.0f); // Same object, different texture
	// Set transformation matrix
	AEGfxSetTransform(logo_trans.m);

	// Draw the mesh
	AEGfxMeshDraw(logo_mesh, AE_GFX_MDM_TRIANGLES);
}

void intro_Free()
{
	AEGfxMeshFree(logo_mesh);
}

void intro_Unload()
{
	AEGfxTextureUnload(logo);
}
