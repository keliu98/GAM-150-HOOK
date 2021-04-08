/*!*************************************************************************
****
\file collision.h
\authors: Tan Egi
		  Tan Wei Wen

\par DP email:  egi.tan@digipen.edu
				t.weiwen@digipen.edu

\par Course: CSD 1450
\par Project: Software Engineering Project 2
\date 160221


\brief
  This is a header file for collision system.
****************************************************************************
***/

#pragma once

#include "pch.h"

/**************************************************************************/
/*!
	Below are collision Flags.
*/
/**************************************************************************/
const unsigned int	FLAG_ACTIVE = 0x00000001;
const unsigned int	FLAG_VISIBLE = 0x00000002;
const unsigned int	FLAG_NON_COLLIDABLE = 0x00000004;

const int	COLLISION_LEFT = 0x00000001;	//0001
const int	COLLISION_RIGHT = 0x00000002;	//0010
const int	COLLISION_TOP = 0x00000004;		//0100
const int	COLLISION_BOTTOM = 0x00000008;	//1000

/**************************************************************************/
/*!
	This enum contain collision types.
*/
/**************************************************************************/
enum TYPE_OBJECT
{
	TYPE_OBJECT_EMPTY,			//0
	TYPE_OBJECT_COLLISION,		//1
	TYPE_OBJECT_HERO,			//2
	TYPE_OBJECT_ENEMY1,			//3
	TYPE_OBJECT_COIN			//4
};

/**************************************************************************/
/*!
	This struct store 2 hotpot spot for each corner.
*/
/**************************************************************************/
struct Corners 
{
	AEVec2 point_1;
	AEVec2 point_2;
}typedef Corners;

/**************************************************************************/
/*!
	This struct store all collision hotspot.
*/
/**************************************************************************/
struct Hotspot
{
	Corners left;
	Corners right;
	Corners top;
	Corners bottom;
}typedef Hotspot;

/**************************************************************************/
/*!
	Updates the Collision.
*/
/**************************************************************************/
void UpdateCollision();

/**************************************************************************/
/*!
	Check binary map collision.
*/
/**************************************************************************/
int	CheckInstanceBinaryMapCollision(AEVec2& pos, AEVec2& velocity);

/**************************************************************************/
/*!
	Snap object back to cell if there is collision.
*/
/**************************************************************************/
void SnapToCell(AEVec2* Coordinate, int flag);

/**************************************************************************/
/*!
	A collision test function to see if two rectangle object collide together.
*/
/**************************************************************************/
bool CollisionIntersection_RectRect(const struct AABB& aabb1, const AEVec2& vel1, const struct AABB& aabb2, const AEVec2& vel2);

/**************************************************************************/
/*!
	A collision test function to see if a point object and rectangle object 
	collide together.
*/
/**************************************************************************/
bool CollisionIntersection_PointRect(const AEVec2 point1, const struct AABB& aabb2);

/**************************************************************************/
/*!
	Create AABB collision points for game objects.
*/
/**************************************************************************/
void create_AABB(AABB& aabb, AEVec2 const& pos, float scale_x, float scale_y);


