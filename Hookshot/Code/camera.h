/*!*************************************************************************
****
\file camera.h
\authors: Tan Egi
		  Tan Wei Wen

\par DP email:  egi.tan@digipen.edu
				t.weiwen@digipen.edu

\par Course: CSD 1450
\par Project: Software Engineering Project 2
\date 020221


\brief
  This is the header file for camera system. 
****************************************************************************
***/

#pragma once

#include "pch.h"

namespace Camera {

	/**************************************************************************/
	/*!
		Created for camera bounding box.
	*/
	/**************************************************************************/
	struct BoundingBox {
		AEVec2 min;
		AEVec2 max;
	} typedef BoundingBox;

}

// store camera bounding box values
static Camera::BoundingBox bounding_box;

/**************************************************************************/
/*!
	This is for testing the camera system.
*/
/**************************************************************************/
void draw_static_obj();

/**************************************************************************/
/*!
	This is for debugging to draw the camera bounding box.
*/
/**************************************************************************/
void draw_cam_bounding_box(AEGfxTexture* texture);

/**************************************************************************/
/*!
	This function set the camera inital position.
*/
/**************************************************************************/
void camera_init(AEVec2 character_pos);

/**************************************************************************/
/*!
	This function update camera position when character exit the camera 
	bounding box.
*/
/**************************************************************************/
void camera_update(AEVec2 character_pos, AEVec2 velocity, float scale);

/**************************************************************************/
/*!
	Get camera's center position value.
*/
/**************************************************************************/
const AEVec2 center_point();

/**************************************************************************/
/*!
	Function to translate cursor.
*/
/**************************************************************************/
void translate_cursor(int& cursor_x, int& cursor_y);

/**************************************************************************/
/*!
	Function to translate UI.
*/
/**************************************************************************/
void translate_UI(AEVec2& pos);
