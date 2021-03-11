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

static const int GRID_SCALE = 40;

void SnapToCell(AEVec2* Coordinate, int Flag)
{
	// *Coordinate = (int)((*Coordinate)) + 0.5f;

	if (Flag == COLLISION_TOP)
	{
		int character_y_index = (int)((Coordinate->y / GRID_SCALE) - 0.5f);
		Coordinate->y = (float)(character_y_index * GRID_SCALE + (GRID_SCALE / 2));
	}
	if (Flag == COLLISION_BOTTOM)
	{
		int character_y_index = (int)((Coordinate->y / GRID_SCALE) + 0.5f);
		Coordinate->y = (float)(character_y_index * GRID_SCALE + (GRID_SCALE / 2));
	}
	if (Flag == COLLISION_LEFT)
	{
		int character_x_index = (int)((Coordinate->x / GRID_SCALE) + 0.5f);
		Coordinate->x = (float)(character_x_index * GRID_SCALE + (GRID_SCALE / 2));
	}
	if (Flag == COLLISION_RIGHT)
	{
		int character_x_index = (int)((Coordinate->x / GRID_SCALE) - 0.5f);
		Coordinate->x = (float)(character_x_index * GRID_SCALE + (GRID_SCALE / 2));
	}

	// Collision for top (make it generalized -> after engine proof)

}

int	CheckInstanceBinaryMapCollision(AEVec2& pos, AEVec2& velocity)
{
	int flag = 0;
	Hotspot item;

	item.right.point_1 = { pos.x + GRID_SCALE / 2 , pos.y + GRID_SCALE / 4 };
	item.right.point_2 = { pos.x + GRID_SCALE / 2 , pos.y - GRID_SCALE / 4 };

	item.left.point_1 = { pos.x - GRID_SCALE / 2, pos.y + GRID_SCALE / 4 };
	item.left.point_2 = { pos.x - GRID_SCALE / 2, pos.y - GRID_SCALE / 4 };

	item.top.point_1 = { pos.x - GRID_SCALE / 4, pos.y + GRID_SCALE / 2 };
	item.top.point_2 = { pos.x + GRID_SCALE / 4, pos.y + GRID_SCALE / 2 };

	item.bottom.point_1 = { pos.x - GRID_SCALE / 4, pos.y - GRID_SCALE / 2 };
	item.bottom.point_2 = { pos.x + GRID_SCALE / 4, pos.y - GRID_SCALE / 2 };

	// check collision
	if (GetCellValue((int)item.right.point_1.x / GRID_SCALE, (int)item.right.point_1.y / GRID_SCALE) ||
		GetCellValue((int)item.right.point_2.x / GRID_SCALE, (int)item.right.point_2.y / GRID_SCALE))
	{
		flag += COLLISION_RIGHT;
		velocity.x = 0;
		SnapToCell(&pos, flag);
		release_hook();
		//std::cout << (int)item.right.point_1.x / 40 << ", " << (int)item.right.point_1.y / 40<< ": ";
		//std::cout << GetCellValue((int)item.right.point_1.x / 40, (int)item.right.point_1.y / 40) << std::endl;
		//std::cout << (int)item.right.point_2.x / 40 << ", " << (int)item.right.point_2.y / 40 << ": ";
		//std::cout << GetCellValue((int)item.right.point_2.x / 40, (int)item.right.point_2.y / 40) << std::endl;
		//std::cout << "RIGHT\n\n";
	}
	if (GetCellValue((int)item.left.point_1.x / GRID_SCALE, (int)item.left.point_1.y / GRID_SCALE) ||
		GetCellValue((int)item.left.point_2.x / GRID_SCALE, (int)item.left.point_2.y / GRID_SCALE))
	{
		flag += COLLISION_LEFT;
		velocity.x = 0;
		SnapToCell(&pos, flag);
		//release_hook();
		//std::cout << (int)item.left.point_1.x / GRID_SCALE << ", " << (int)item.left.point_1.y / GRID_SCALE << ": ";
		//std::cout << GetCellValue((int)item.left.point_1.x / GRID_SCALE, (int)item.left.point_1.y / GRID_SCALE) << std::endl;
		//std::cout << (int)item.left.point_2.x /GRID_SCALE << ", " << (int)item.left.point_2.y / GRID_SCALE<< ": ";
		//std::cout << GetCellValue((int)item.left.point_2.x / GRID_SCALE, (int)item.left.point_2.y / GRID_SCALE) << std::endl;
		//std::cout << "LEFT\n\n";
	}
	if (GetCellValue((int)item.top.point_1.x / GRID_SCALE, (int)item.top.point_1.y / GRID_SCALE) ||
		GetCellValue((int)item.top.point_2.x / GRID_SCALE, (int)item.top.point_2.y / GRID_SCALE))
	{
		flag += COLLISION_TOP;
		velocity = { 0.0f, -0.01f };
		SnapToCell(&pos, flag);
		//release_hook();
		//std::cout << (int)item.top.point_1.x << ", " << (int)item.top.point_1.y << ": ";
		//std::cout << GetCellValue((int)item.top.point_1.x, (int)item.top.point_1.y) << std::endl;
		//std::cout << (int)item.top.point_2.x << ", " << (int)item.top.point_2.y << ": ";
		//std::cout << GetCellValue((int)item.top.point_2.x, (int)item.top.point_2.y) << std::endl;
		//std::cout << "TOP\n\n";
	}
	if (GetCellValue((int)item.bottom.point_1.x / GRID_SCALE, (int)item.bottom.point_1.y / GRID_SCALE) ||
		GetCellValue((int)item.bottom.point_2.x / GRID_SCALE, (int)item.bottom.point_2.y / GRID_SCALE))
	{
		flag += COLLISION_BOTTOM;
		velocity.y = 0.0f ;
		//std::cout << (int)item.bottom.point_1.x / GRID_SCALE << ", " << (int)item.bottom.point_1.y / GRID_SCALE << ": ";
		//std::cout << GetCellValue((int)item.bottom.point_1.x / GRID_SCALE, (int)item.bottom.point_1.y / GRID_SCALE) << std::endl;
		//std::cout << (int)item.bottom.point_2.x /GRID_SCALE << ", " << (int)item.bottom.point_2.y / GRID_SCALE<< ": ";
		//std::cout << GetCellValue((int)item.bottom.point_2.x / GRID_SCALE, (int)item.bottom.point_2.y / GRID_SCALE) << std::endl;
		//std::cout << "BOTTOM\n\n";
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

bool CollisionIntersection_PointRect(const AEVec2 point1, const AABB& aabb2)
{
	//static collision
	if (point1.x > aabb2.min.x &&
		point1.x < aabb2.max.x &&
		point1.y > aabb2.min.y &&
		point1.y < aabb2.max.y)
	{
		return true;
	}

	return false;	
}
