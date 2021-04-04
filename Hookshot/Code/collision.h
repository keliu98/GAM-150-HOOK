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
#include "ObjectManager.h"
extern const int GRID_SCALE;

//Flags
const unsigned int	FLAG_ACTIVE = 0x00000001;
const unsigned int	FLAG_VISIBLE = 0x00000002;
const unsigned int	FLAG_NON_COLLIDABLE = 0x00000004;

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

// Updates the Collision
void UpdateCollision();

// check binary map collision
int	CheckInstanceBinaryMapCollision(AEVec2& pos, AEVec2& velocity);

// snap object back to cell if there is collision
void SnapToCell(AEVec2* Coordinate, int flag);

/**************************************************************************/
/*!
	A collision test function to see if two rectangle object collide together.
*/
/**************************************************************************/

bool CollisionIntersection_RectRect(const struct AABB& aabb1, const AEVec2& vel1, const struct AABB& aabb2, const AEVec2& vel2);

/**************************************************************************/
/*!
	A collision test function to see if a point object and rectangle object collide together.
*/
/**************************************************************************/
bool CollisionIntersection_PointRect(const AEVec2 point1, const struct AABB& aabb2);

void create_AABB(AABB& aabb, AEVec2 const& pos, float scale_x, float scale_y);


