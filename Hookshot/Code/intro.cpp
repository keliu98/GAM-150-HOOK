#include "intro.h"

static const int MAX_LOGO = 2;
//Pointer to square mesh
static AEGfxVertexList* logo_mesh;
static AEGfxTexture* logo[MAX_LOGO];
static float transparency[MAX_LOGO];
static bool shown[MAX_LOGO];
static bool completed;
static int index;

void intro_Load()
{
	AEGfxMeshStart();

	AEGfxTriAdd(
		-2.7f, -1.0f, 0x00FF00FF, 0.0f, 1.0f,
		2.7f, -1.0f, 0x00FFFF00, 1.0f, 1.0f,
		-2.7f, 1.0f, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		2.7f, -1.0f, 0x00FFFFFF, 1.0f, 1.0f,
		2.7f, 1.0f, 0x00FFFFFF, 1.0f, 0.0f,
		-2.7f, 1.0f, 0x00FFFFFF, 0.0f, 0.0f);


	logo_mesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(logo_mesh, "Failed to create logo mesh!!");

	logo[0] = AEGfxTextureLoad("../Images/DigiPen_Singapore_WEB_WHITE.png");
	logo[1] = AEGfxTextureLoad("../Images/hookshot_logo.png");
}

void intro_Initialize()
{
	completed = false;
	index = 0;

	for (int i{ 0 }; i < MAX_LOGO; ++i)
	{
		shown[i] = false;
		transparency[i] = 0;
	}
}

void intro_Update()
{
	if (index != 0)
		skip_intro();

	if (!completed)
	{
		if (!shown[index] && transparency[index] <= 1)
		{
			transparency[index] += 0.01f;
			if (transparency[index] >= 1)
				shown[index] = true;
		}

		else
		{
			transparency[index] -= 0.01f;

			if (transparency[index] <= 0)
			{
				if (index == MAX_LOGO - 1)
				{
					completed = true;
				}
				else
					++index;
			}
		}
	}
	else
		next = GS_MENU;
}

void intro_Draw()
{
	static char text[100];
	memset(text, 0, 100 * sizeof(char));

	AEMtx33	trans, scale, logo_trans;
	// Compute the scalling matrix
	AEMtx33Scale(&scale, 100, 100);
	// Compute the translation matrix
	AEMtx33Trans(&trans, 0, 0);
	//Combining the matrix
	AEMtx33Concat(&logo_trans, &trans, &scale);

	// Drawing object  - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);	// set to texture
		//For the texture to blend into the game.
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(transparency[index]);
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set texture
	AEGfxTextureSet(logo[index], 0.0f, 0.0f); // Same object, different texture
	// Set transformation matrix
	AEGfxSetTransform(logo_trans.m);
	// Draw the mesh
	AEGfxMeshDraw(logo_mesh, AE_GFX_MDM_TRIANGLES);

	// print copyright
	sprintf_s(text, "©2021 DigiPen Corporation (Singapore), All Rights Reserved");
	PrintText(text, SMALL, { -0.68f, -0.85f });
}

void intro_Free()
{
	AEGfxMeshFree(logo_mesh);
}

void intro_Unload()
{
	for (int i{ 0 }; i < MAX_LOGO; ++i)
		AEGfxTextureUnload(logo[i]);
}
