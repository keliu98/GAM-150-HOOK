/******************************************************************************/
/*!
\file         camera.h
\author       Tan Egi, egi.tan, 2002777
\par          egi.tan@digipen.edu
\date         March 2, 2021
\brief        This is the header file for camera system. 

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior 
written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once

#include "pch.h"

namespace Camera {
struct BoundingBox {
	AEVec2 min;
	AEVec2 max;
} typedef BoundingBox;

}
static Camera::BoundingBox bounding_box;

/// <summary>
///		This is for testing the camera system.
/// </summary>
void draw_static_obj();

/// <summary>
///		This is for debugging to draw the camera bounding box.
/// </summary>
void draw_cam_bounding_box(AEVec2 point1 = bounding_box.min, AEVec2 point2 = bounding_box.max);

/// <summary>
///		This function set the camera inital position. 
/// </summary>
/// <param name="character_pos"></param>
void camera_init(AEVec2 character_pos);

/// <summary>
///		This function update camera position when character exit the camera bounding box.
/// </summary>
/// <param name="character_pos"></param>
void camera_update(AEVec2 character_pos, AEVec2 velocity, float scale);


//ADDED IN NEW FUNCTION TO TRANSLATE CURSOR - WEI WEN
void translate_cursor(int& cursor_x, int& cursor_y);
