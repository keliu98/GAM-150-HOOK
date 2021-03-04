/******************************************************************************/
/*!
\file         collision.h
\author       Tan Egi, egi.tan, 2002777
\par          egi.tan@digipen.edu
\date         February 16, 2021
\brief        This is a header file for collision system.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/
#pragma once

#include "pch.h"


const int	COLLISION_LEFT = 0x00000001;	//0001
const int	COLLISION_RIGHT = 0x00000002;	//0010
const int	COLLISION_TOP = 0x00000004;	//0100
const int	COLLISION_BOTTOM = 0x00000008;	//1000

enum TYPE_OBJECT
{
	TYPE_OBJECT_EMPTY,			//0
	TYPE_OBJECT_COLLISION,		//1
	TYPE_OBJECT_HERO,			//2
	TYPE_OBJECT_ENEMY1,			//3
	TYPE_OBJECT_COIN			//4
};

struct Corners 
{
	AEVec2 point_1;
	AEVec2 point_2;
}typedef Corners;

struct Hotspot
{
	Corners left;
	Corners right;
	Corners top;
	Corners bottom;
}typedef Hotspot;

// check binary map collision
int	CheckInstanceBinaryMapCollision(float PosX, float PosY, float scaleX, float scaleY);

// snap object back to cell if there is collision
void SnapToCell(float* Coordinate);

/**************************************************************************/
/*!
	A collision test function to see if two rectangle object collide together.
*/
/**************************************************************************/
bool CollisionIntersection_RectRect(const struct AABB& aabb1, const AEVec2& vel1, const struct AABB& aabb2, const AEVec2& vel2);
