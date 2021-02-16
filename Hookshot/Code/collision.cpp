/******************************************************************************/
/*!
\file         collision.cpp
\author       Tan Egi, egi.tan, 2002777
\par          egi.tan@digipen.edu
\date         February 16, 2021
\brief        This file detect collision between two rectangle object.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/******************************************************************************/

#include "collision.h"

/**************************************************************************/
/*!
	A collision test function to see if two rectangle object collide together.
*/
/**************************************************************************/
bool CollisionIntersection_RectRect(const AABB& aabb1, const AEVec2& vel1, const AABB& aabb2, const AEVec2& vel2)
{
	// Step 1: Check for static collision detection between rectangles (before moving)
	if (aabb1.min.x < aabb2.max.x &&
		aabb1.min.y < aabb2.max.y &&
		aabb1.max.x > aabb2.min.x &&
		aabb1.max.y > aabb2.min.y)
	{
		return true;
	}

	// Step 2: Check for dynamic collision
	AEVec2 tFirst = {0, 0};
	AEVec2 tLast = { g_dt, g_dt };
	AEVec2 velocity_1 = vel1, velocity_2 = vel2, Vb;
	bool x_col = false, y_col = false;
	AEVec2Sub(&Vb, &velocity_2, &velocity_1);

	// Step 3: Working with one dimension (x-axis).
	if (Vb.x < 0)
	{
		// case 1
		if (aabb1.min.x > aabb2.max.x)
		{
			return false;
		}
		// case 4
		if (aabb1.max.x < aabb2.min.x)
		{
			tFirst.x = AEMax((aabb1.max.x - aabb2.min.x) / Vb.x, tFirst.x);
		}
		if (aabb1.min.x < aabb2.max.x)
		{
			tLast.x = AEMin((aabb1.min.x - aabb2.max.x) / Vb.x, tLast.x);
		}
	}

	else if (Vb.x > 0)
	{
		// case 3
		if (aabb1.max.x < aabb2.min.x)
		{
			return false;
		}
		// case 2
		if (aabb1.min.x > aabb2.max.x)
		{
			tFirst.x = AEMax((aabb1.min.x - aabb2.max.x) / Vb.x, tFirst.x);
		}
		if (aabb1.max.x > aabb2.min.x)
		{
			tLast.x = AEMin((aabb1.max.x - aabb2.min.x) / Vb.x, tLast.x);
		}
	}

	else if (Vb.x == 0)
	{
		x_col = false;
	}

	// case 5
	if (tFirst.x > tLast.x)
		return 0;

	// Step 4: Repeat step 3 on the y-axis
	if (Vb.y < 0)
	{
		// case 1
		if (aabb1.min.y > aabb2.max.y)
		{
			return 0;
		}
		// case 4
		if (aabb1.max.y < aabb2.min.y)
		{
			tFirst.y = AEMax((aabb1.max.y - aabb2.min.y) / Vb.y, tFirst.y);
		}
		if (aabb1.min.y < aabb2.max.y)
		{
			tLast.y = AEMin((aabb1.min.y - aabb2.max.y) / Vb.y, tLast.y);
		}
	}

	else if (Vb.y > 0)
	{
		// case 3
		if (aabb1.max.y < aabb2.min.y)
		{
			return 0;
		}
		// case 2
		if (aabb1.min.y > aabb2.max.y)
		{
			tFirst.y = AEMax((aabb1.min.y - aabb2.max.y) / Vb.y, tFirst.y);
		}
		if (aabb1.max.y > aabb2.min.y)
		{
			tLast.y = AEMin((aabb1.max.y - aabb2.min.y) / Vb.y, tLast.y);
		}
	}

	// For static
	else if (Vb.y == 0)
	{
		y_col = false;
	}

	// case 5
	if (tFirst.y > tLast.y)
		return 0;


	// Step 5: Otherwise the rectangles intersect
	return (x_col && y_col);
}