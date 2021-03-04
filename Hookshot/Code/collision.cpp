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

void SnapToCell(float* Coordinate)
{
	*Coordinate = (int)(*Coordinate) + 0.5f;
}

int	CheckInstanceBinaryMapCollision(float PosX, float PosY, float scaleX, float scaleY)
{
	int flag = 0;
	Hotspot item;

	item.right.point_1 = { PosX + scaleX / 2 , PosY + scaleY / 4 };
	item.right.point_2 = { PosX + scaleX / 2 , PosY - scaleY / 4 };

	item.left.point_1 = { PosX - scaleX / 2, PosY + scaleY / 4 };
	item.left.point_2 = { PosX - scaleX / 2, PosY - scaleY / 4 };

	item.top.point_1 = { PosX - scaleX / 4, PosY + scaleY / 2 };
	item.top.point_2 = { PosX + scaleX / 4, PosY + scaleY / 2 };

	item.bottom.point_1 = { PosX - scaleX / 4, PosY - scaleY / 2 };
	item.bottom.point_2 = { PosX + scaleX / 4, PosY - scaleY / 2 };

	// check collision
	if (GetCellValue((int)item.right.point_1.x, (int)item.right.point_1.y) ||
		GetCellValue((int)item.right.point_2.x, (int)item.right.point_2.y))
	{
		flag += COLLISION_RIGHT;
	}
	if (GetCellValue((int)item.left.point_1.x, (int)item.left.point_1.y) ||
		GetCellValue((int)item.left.point_2.x, (int)item.left.point_2.y))
	{
		flag += COLLISION_LEFT;
	}
	if (GetCellValue((int)item.top.point_1.x, (int)item.top.point_1.y) ||
		GetCellValue((int)item.top.point_2.x, (int)item.top.point_2.y))
	{
		flag += COLLISION_TOP;
	}
	if (GetCellValue((int)item.bottom.point_1.x, (int)item.bottom.point_1.y) ||
		GetCellValue((int)item.bottom.point_2.x, (int)item.bottom.point_2.y))
	{
		flag += COLLISION_BOTTOM;
	}

	return flag;
}

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
	float tFirst = 0;
	float tLast = g_dt;
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
			tFirst = AEMax((aabb1.max.x - aabb2.min.x) / Vb.x, tFirst);
		}
		if (aabb1.min.x < aabb2.max.x)
		{
			tLast = AEMin((aabb1.min.x - aabb2.max.x) / Vb.x, tLast);
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
			tFirst = AEMax((aabb1.min.x - aabb2.max.x) / Vb.x, tFirst);
		}
		if (aabb1.max.x > aabb2.min.x)
		{
			tLast = AEMin((aabb1.max.x - aabb2.min.x) / Vb.x, tLast);
		}
	}

	else if (Vb.x == 0)
	{
		x_col = false;
	}

	// case 5
	if (tFirst > tLast)
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
			tFirst = AEMax((aabb1.max.y - aabb2.min.y) / Vb.y, tFirst);
		}
		if (aabb1.min.y < aabb2.max.y)
		{
			tLast = AEMin((aabb1.min.y - aabb2.max.y) / Vb.y, tLast);
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
			tFirst = AEMax((aabb1.min.y - aabb2.max.y) / Vb.y, tFirst);
		}
		if (aabb1.max.y > aabb2.min.y)
		{
			tLast = AEMin((aabb1.max.y - aabb2.min.y) / Vb.y, tLast);
		}
	}

	// For static
	else if (Vb.y == 0)
	{
		y_col = false;
	}

	// case 5
	if (tFirst > tLast)
		return 0;


	// Step 5: Otherwise the rectangles intersect
	return (x_col && y_col);
}

