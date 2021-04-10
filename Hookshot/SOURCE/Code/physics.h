/*!*************************************************************************
****
\file physics.h
\par Project: Hookshot
\authors: Tan Wei Wen (100%)

\par DP email:  t.weiwen@digipen.edu

\par Course: CSD 1450
\date 050421

\brief
This file contains the interface for the physics system of the game. Most used
for the game state.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. All
				rights reserved.

****************************************************************************
***/

#pragma once
#include "pch.h"
/**************************************************************************/
/*!
	Intialises the physics variables used for the game
*/
/**************************************************************************/

void physics_intialize();

/**************************************************************************/
/*!
	Updates the physics of the game
*/
/**************************************************************************/

void physics_update();

/**************************************************************************/
/*!
	Helper function to set the acceleration to the the velocity based 
	on delta time
*/
/**************************************************************************/

void set_accel_to_vel(AEVec2& vel, AEVec2 dir, float const accel);

/**************************************************************************/
/*!
	Helper function to set the velocity to the the position based
	on delta time. Uses a normalised directional vector and a scalar velocity
*/
/**************************************************************************/

void set_vel_to_pos(AEVec2& pos, AEVec2 dir, float &vel);

/**************************************************************************/
/*!
	Helper function to set the velocity to the the position based
	on delta time. TUses a velocity vector that is already scaled.
*/
/**************************************************************************/

void set_vel_to_pos(AEVec2& pos, AEVec2& vel);

/**************************************************************************/
/*!
	Helper to create the y_velocity by taking in a height and the gravity
*/
/**************************************************************************/

float create_vel_height(float height, float gravity);

/**************************************************************************/
/*!
	Helper to calculate the knockback of a object.
*/
/**************************************************************************/

void calculate_knockback(AEVec2& pos1, AEVec2& pos2, AEVec2& velocity, AEVec2 knockback);
