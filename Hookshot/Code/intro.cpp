/*!*************************************************************************
****
\file intro.cpp
\par Project: Hookshot
\authors: Tan Egi (100%)
\par DP email: egi.tan@digipen.edu

\brief
This is a implementation file for the logo introduction before showing the 
game main menu.

\par Course: CSD 1450
\date 090421

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

****************************************************************************
***/

#include "intro.h"

static const int MAX_LOGO = 2;			// Number of logo to show
static AEGfxVertexList* logo_mesh;		// logo mesh (rectangle)
static AEGfxTexture* logo[MAX_LOGO];	// Array of texture containing logo
static float transparency[MAX_LOGO];	// transparency for fading in / out
static bool shown[MAX_LOGO];			// bool to track which have been shown
static bool completed;					// bool to track if finish showing all
static int index;						// track which logo it is showing

void intro_Load()
{
	// create mesh
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

	// load textures
	logo[0] = AEGfxTextureLoad("../Images/DigiPen_Singapore_WEB_WHITE.png");
	logo[1] = AEGfxTextureLoad("../Images/hookshot_logo.png");
}

void intro_Initialize()
{
	// init variables
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
	// for bypass intro screen
	if (index != 0)
		skip_intro();

	if (!completed)
	{
		// fade in each logo
		if (!shown[index] && transparency[index] <= 1)
		{
			transparency[index] += 0.01f;
			if (transparency[index] >= 1)
				shown[index] = true;
		}

		// fade out each logo
		else
		{
			transparency[index] -= 0.01f;

			if (transparency[index] <= 0)
			{
				// check if finish
				if (index == MAX_LOGO - 1)
				{
					completed = true;
				}
				// proceed to next
				else
					++index;
			}
		}
	}

	// done with screening logo
	else
		next = GS_MENU;
}

void intro_Draw()
{
	static char text[100];
	memset(text, 0, 100 * sizeof(char));

	AEMtx33	trans, scale, logo_trans;
	AEMtx33Scale(&scale, 100, 100);
	AEMtx33Trans(&trans, 0, 0);
	AEMtx33Concat(&logo_trans, &trans, &scale);

	// Drawing object 
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetTransparency(transparency[index]);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	AEGfxTextureSet(logo[index], 0.0f, 0.0f);
	AEGfxSetTransform(logo_trans.m);
	AEGfxMeshDraw(logo_mesh, AE_GFX_MDM_TRIANGLES);

	// print copyright
	sprintf_s(text, "©2021 DigiPen Corporation (Singapore), All Rights Reserved");
	PrintText(text, SMALL, { -0.68f, -0.85f });
}

void intro_Free()
{
	// free mesh
	AEGfxMeshFree(logo_mesh);
}

void intro_Unload()
{
	// free textures
	for (int i{ 0 }; i < MAX_LOGO; ++i)
		AEGfxTextureUnload(logo[i]);
}
