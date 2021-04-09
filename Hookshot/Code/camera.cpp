/*!*************************************************************************
****
\file camera.cpp
\par Project: Hookshot
\authors: Tan Egi (90%)
		  Tan Wei Wen (10%)
\par DP email: egi.tan@digipen.edu
			   t.weiwen@digipen.edu
\date 090421

\brief
This file contain the camera system function definition.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

****************************************************************************
***/

#include "camera.h"


static AEVec2 center, cam_max, dist;	// camera variable
static bool loadOnce = false;			// init variable only once

void draw_static_obj()
{
	// create mesh
	AEGfxMeshStart();

	AEGfxVertexAdd(40.0f, 140.0f, 0x808080, 0.0f, 0.0f);
	AEGfxVertexAdd(10.0f, 50.0f, 0x808080, 0.0f, 0.0f);

	AEGfxVertexList* pMeshLine = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMeshLine, "Failed to create line mesh!!");
	
	// draw mesh
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxMeshDraw(pMeshLine, AE_GFX_MDM_LINES_STRIP);

	// free mesh
	AEGfxMeshFree(pMeshLine);
}

void draw_cam_bounding_box(AEGfxTexture* texture)
{
	// Create mesh
	AEGfxMeshStart();

	AEGfxVertexAdd(bounding_box.min.x, bounding_box.min.y, 0x000000, 0.0f, 0.0f);
	AEGfxVertexAdd(bounding_box.min.x, bounding_box.max.y, 0x000000, 0.0f, 0.0f);
	AEGfxVertexAdd(bounding_box.max.x, bounding_box.max.y, 0x000000, 0.0f, 0.0f);
	AEGfxVertexAdd(bounding_box.max.x, bounding_box.min.y, 0x000000, 0.0f, 0.0f);
	AEGfxVertexAdd(bounding_box.min.x, bounding_box.min.y, 0x000000, 0.0f, 0.0f);

	AEGfxVertexList* pMeshLine2 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMeshLine2, "Failed to create line mesh!!");

	// Draw bounding box
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);				// set to texture
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);			// no tint
	AEGfxTextureSet(texture, 0.0f, 0.0f);				// set texture
	AEGfxSetPosition(0.0f, 0.0f);						// set position
	AEGfxMeshDraw(pMeshLine2, AE_GFX_MDM_LINES_STRIP);	// set draw mode
	AEGfxSetTransparency(0.5f);							// set transparency
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);					// set blend mode
	AEGfxMeshFree(pMeshLine2);							// free mesh
}

void camera_init(AEVec2 character_pos) {
	// set camera center position
	center = character_pos;
	// set camera bounding box distance
	cam_max = { character_pos.x + (40.0f * 4), character_pos.y + (40.0f * 3) };

	// find distance between character & bounding box max point
	if (!loadOnce)
	{
		AEVec2Sub(&dist, &center, &cam_max);
		if (dist.x < 0)
			dist.x = dist.x * -1;
		if (dist.y < 0)
			dist.y = dist.y * -1;
		loadOnce = true;
	}

	// update bounding box based on camera position & distance calculated 
	AEVec2Add(&bounding_box.max, &center, &dist);
	AEVec2Sub(&bounding_box.min, &center, &dist);

	// set camera at character position
	AEGfxSetCamPosition(center.x, center.y);
}


// Create a small bounding box for player
void camera_update(AEVec2 character_pos, AEVec2 velocity, float character_scale)
{
	// update bounding box to based on distance calculated
	AEVec2Add(&bounding_box.max, &center, &dist);
	AEVec2Sub(&bounding_box.min, &center, &dist);

	// move left 
	if (velocity.x < 0.01f) 
	{
		if ((character_pos.x - character_scale) < bounding_box.min.x)
		{
			//translate the camera by the distance of when it exits the bounding box
			center.x -= bounding_box.min.x - character_pos.x + character_scale;
			AEGfxSetCamPosition(center.x, center.y);
		}
	}

	// move right
	if (velocity.x > 0.01f)
	{
		if ((character_pos.x + character_scale) > bounding_box.max.x)
		{
			//translate the camera by the distance of when it exits the bounding box
			center.x += character_pos.x + character_scale - bounding_box.max.x;
			AEGfxSetCamPosition(center.x, center.y);
		}
	}

	// move top
	if (velocity.y > 0.01f)
	{
		if ((character_pos.y + character_scale) > bounding_box.max.y)
		{
			//translate the camera by the distance of when it exits the bounding box
			center.y += character_pos.y + character_scale - bounding_box.max.y;
			AEGfxSetCamPosition(center.x, center.y);
		}
	}

	// move bottom
	if (velocity.y < 0.01f)
	{
		if ((character_pos.y - character_scale) < bounding_box.min.y)
		{
			//translate the camera by the distance of when it exits the bounding box
			center.y -= bounding_box.min.y - character_pos.y + character_scale;
			AEGfxSetCamPosition(center.x, center.y);
		}
	}

}

// return camera center point
const AEVec2 center_point()
{
	return center;
}


// Function to translate the cursor position when the camera moves
void translate_cursor(int& cursor_x, int& cursor_y)
{
	//Moving the origin of the cursor from the top left to center of the screen.
	cursor_x = cursor_x - WINDOW_WIDTH / 2;
	cursor_y = (cursor_y - WINDOW_HEIGHT / 2) * -1;

	//For states where camera is not translated e.g menu
	if (current != GS_MENU)
	{
		cursor_x += static_cast <int>(center.x);
		cursor_y += static_cast <int>(center.y);
	}
}

//Function to translate UI, similar to translate cursor but no need to shift origin to center.
void translate_UI(AEVec2& pos)
{
	if (current != GS_MENU)
	{
		pos.x += center.x;
		pos.y += center.y;
	}
}

