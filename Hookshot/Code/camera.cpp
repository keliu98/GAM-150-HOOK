/******************************************************************************/
/*!
\file         camera.cpp
\author       Tan Egi, egi.tan, 2002777
\par          egi.tan@digipen.edu
\date         March 2, 2021
\brief        This file contain the camera system function definition. 

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior 
written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#include "camera.h"

static AEVec2 center;
AEVec2 scale, win_min, win_max, dist;
static int counter = 0;

void draw_static_obj()
{
	AEGfxMeshStart();

	AEGfxVertexAdd(40.0f, 140.0f, 0x808080, 0.0f, 0.0f);
	AEGfxVertexAdd(10.0f, 50.0f, 0x808080, 0.0f, 0.0f);

	AEGfxVertexList* pMeshLine = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMeshLine, "Failed to create line mesh!!");

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxMeshDraw(pMeshLine, AE_GFX_MDM_LINES_STRIP);

	AEGfxMeshFree(pMeshLine);
}

void draw_cam_bounding_box(AEVec2 point1, AEVec2 point2)
{
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	AEGfxVertexAdd(point1.x, point1.y, 0x808080, 0.0f, 0.0f);
	AEGfxVertexAdd(point1.x, point2.y, 0x808080, 0.0f, 0.0f);
	AEGfxVertexAdd(point2.x, point2.y, 0x808080, 0.0f, 0.0f);
	AEGfxVertexAdd(point2.x, point1.y, 0x808080, 0.0f, 0.0f);
	AEGfxVertexAdd(point1.x, point1.y, 0x808080, 0.0f, 0.0f);

	/*AEGfxVertexAdd(bounding_box.min.x, bounding_box.min.y, 0x808080, 0.0f, 0.0f);
	AEGfxVertexAdd(bounding_box.min.x, bounding_box.max.y, 0x808080, 0.0f, 0.0f);
	AEGfxVertexAdd(bounding_box.max.x, bounding_box.max.y, 0x808080, 0.0f, 0.0f);
	AEGfxVertexAdd(bounding_box.max.x, bounding_box.min.y, 0x808080, 0.0f, 0.0f);
	AEGfxVertexAdd(bounding_box.min.x, bounding_box.min.y, 0x808080, 0.0f, 0.0f);*/

	AEGfxVertexList* pMeshLine2 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMeshLine2, "Failed to create line mesh!!");

	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxSetPosition(0.0f, 0.0f);
	AEGfxMeshDraw(pMeshLine2, AE_GFX_MDM_LINES_STRIP);

	AEGfxMeshFree(pMeshLine2);
}

void camera_init(AEVec2 character_pos) {
	center = character_pos;
	scale = { AEGfxGetWinMaxX() * 0.5f, AEGfxGetWinMaxY() * 0.7f };
	win_min = { AEGfxGetWinMinX(), AEGfxGetWinMinY() };
	win_max = { AEGfxGetWinMaxX(), AEGfxGetWinMaxY() };

	// Set bounding box min
	AEVec2Add( &bounding_box.min, &win_min,  &scale);
	// Set boundng box max
	AEVec2Sub(&bounding_box.max, &win_max, &scale);

	// Set camera at character position
	AEGfxGetCamPosition(&center.x, &center.y);
	AEVec2Sub(&dist, &bounding_box.max, &character_pos);
}


// Create a small bounding box for player - 3/4 of the screen top and bottom
void camera_update(AEVec2 const character_pos, AEVec2 velocity, float scale)
{
	draw_cam_bounding_box(bounding_box.min, bounding_box.max);
	// set bounding box min
	AEVec2Add(&bounding_box.max, &center, &dist);
	// set boundng box max
	AEVec2Sub(&bounding_box.min, &center, &dist);

	// move left 
	if (velocity.x < 0.01f)
	{
		if ((character_pos.x - scale) < bounding_box.min.x)
		{
			center.x -= bounding_box.min.x - character_pos.x + scale; //translate the camera by the distance of when it exits the bounding box
			AEGfxSetCamPosition(center.x, center.y);
		}
	}

	// move right
	if (velocity.x > 0.01f)
	{
		if ((character_pos.x + scale) > bounding_box.max.x)
		{
			center.x += character_pos.x + scale - bounding_box.max.x;
			AEGfxSetCamPosition(center.x, center.y);
			// printf("Touching bounding box: %d\n", counter++);
			//center.x += velocity.x * g_dt;
			//AEGfxSetCamPosition(center.x, center.y);
		}
	}

	// move top
	if (velocity.y > 0.01f)
	{
		if ((character_pos.y + scale) > bounding_box.max.y)
		{
			center.y += character_pos.y + scale - bounding_box.max.y;
			AEGfxSetCamPosition(center.x, center.y);
			//center.y += velocity.y * g_dt;
			//AEGfxSetCamPosition(center.x, center.y);
		}
	}

	// move bottom
	if (velocity.y < 0.01f)
	{
		if ((character_pos.y - scale) < bounding_box.min.y)
		{
			center.y -= bounding_box.min.y - character_pos.y + scale;
			AEGfxSetCamPosition(center.x, center.y);
		}
	}

}


//FUNCTION TO TRANSLATE THE CURSOR POSITION WHEN THE CAMERA MOVES AS WELL.
void translate_cursor(int& cursor_x, int& cursor_y)
{
	cursor_x += static_cast <int>(center.x);
	cursor_y += static_cast <int>(center.y);
}

