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

static AEVec2 move_spd{ 2, 2};
static AEVec2 center;

void camera_init(AEVec2 const character_pos) {
	center = character_pos;
	AEVec2 win_min = { AEGfxGetWinMinX(), AEGfxGetWinMinY() };
	AEVec2 win_max = { AEGfxGetWinMaxX(), AEGfxGetWinMaxY() };

	// Set bounding box min
	AEVec2Scale(&bounding_box.min, &win_max, 0.25);
	AEVec2Add(&bounding_box.min, &win_min, &bounding_box.min);

	// Set boundng box max
	AEVec2Scale(&bounding_box.max, &win_max, 0.25);
	AEVec2Sub(&bounding_box.max, &win_max, &bounding_box.max);

	// Set camera at character position
	AEGfxGetCamPosition(&center.x, &center.y);

	printf("Min: %f | %f\n", bounding_box.min.x, bounding_box.min.y);
	printf("Max: %f | %f\n", bounding_box.max.x, bounding_box.max.y);
	printf("Center: %f | %f\n", center.x, center.y);
}


// Create a small bounding box for player - 3/4 of the screen top and bottom
void camera_update(AEVec2 const character_pos)
{
	// AEGfxGetCamPosition(&pos.x, &pos.y);

	// move left
	if (character_pos.x < bounding_box.min.x)
	{
		center.x -= move_spd.x;
		AEGfxSetCamPosition(center.x, center.y);
		bounding_box.min.x -= move_spd.x;
		bounding_box.max.x -= move_spd.x;
	}

	// move right
	if (character_pos.x > bounding_box.max.x)
	{
		center.x += move_spd.x;
		AEGfxSetCamPosition(center.x, center.y);
		bounding_box.min.x += move_spd.x;
		bounding_box.max.x += move_spd.x;

		printf("Min: %f | %f\n", bounding_box.min.x, bounding_box.min.y);
		printf("Max: %f | %f\n", bounding_box.max.x, bounding_box.max.y);
		printf("Center: %f | %f\n", center.x, center.y);
	}

	// move bottom
	if (character_pos.y < bounding_box.min.y)
	{
		center.y -= move_spd.y;
		AEGfxSetCamPosition(center.x, center.y);
		bounding_box.min.y -= move_spd.y;
		bounding_box.max.y -= move_spd.y;
	}

	// move top
	if (character_pos.y > bounding_box.max.y)
	{
		center.y += move_spd.y;
		AEGfxSetCamPosition(center.x, center.y);
		bounding_box.min.y += move_spd.y;
		bounding_box.max.y += move_spd.y;
	}
}

