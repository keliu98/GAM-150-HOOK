/*!*************************************************************************
****
\file collision.cpp
\par Project: Hookshot
\authors: Tan Egi (60%)
		  Tan Wei Wen (35%)
		  Yong Hui (5%)
\par DP email: egi.tan@digipen.edu
			   t.weiwen@digipen.edu
			   l.yonghui@digipen.edu
\date 160221

\brief
This file contains implementation for collision detection between game
objects.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

****************************************************************************
***/

#include "collision.h"

const int GRID_SCALE = 40;

void UpdateCollision()
{
	// update collision flag and snap plater back to grid
	character->grid_collision_flag = CheckInstanceBinaryMapCollision(character->pos, character->velocity);
	SnapToCell(&character->pos, character->grid_collision_flag);

	// track how many shots left
	if (character->velocity.y < 0.01f && (character->grid_collision_flag & COLLISION_BOTTOM) == COLLISION_BOTTOM)
	{
		character->char_state = not_jumping;
		ammo = 3;
		ammoD = 3;
	}

	// collision for enemies
	for (Enemy& enemy : enemies) {
		enemy.grid_collision_flag = CheckInstanceBinaryMapCollision(enemy.pos, enemy.velocity);
		SnapToCell(&enemy.pos, enemy.grid_collision_flag);
		//jump logic
		if (enemy.velocity.y < 0.01f && (enemy.grid_collision_flag & COLLISION_BOTTOM) == COLLISION_BOTTOM)
		{
			enemy.jump_state = not_jumping;
		}
	}

	// create AABB points
	create_AABB(character->aabb, character->pos, character->scale, character->scale);
}

void SnapToCell(AEVec2* Coordinate, int Flag)
{
	int character_x_index = 0;
	int character_y_index = 0;

	// for top collision
	if ((Flag & COLLISION_TOP) == COLLISION_TOP)
	{
		character_y_index = (int)((Coordinate->y / GRID_SCALE) - 0.5f);
		Coordinate->y = (float)(character_y_index * GRID_SCALE + (GRID_SCALE / 2));
	}
	// for bottom collision
	if ((Flag & COLLISION_BOTTOM) == COLLISION_BOTTOM)
	{
		character_y_index = (int)((Coordinate->y / GRID_SCALE) + 0.5f);
		Coordinate->y = (float)(character_y_index * GRID_SCALE + (GRID_SCALE / 2) - 2.5f);
	}
	// for left collision
	if ((Flag & COLLISION_LEFT) == COLLISION_LEFT)
	{
		character_x_index = (int)((Coordinate->x / GRID_SCALE) + 0.5f);
		Coordinate->x = (float)(character_x_index * GRID_SCALE + (GRID_SCALE / 2));
	}
	// for right collision
	if ((Flag & COLLISION_RIGHT) == COLLISION_RIGHT)
	{
		character_x_index = (int)((Coordinate->x / GRID_SCALE) - 0.5f);
		Coordinate->x = (float)(character_x_index * GRID_SCALE + (GRID_SCALE / 2));
	}
}

int	CheckInstanceBinaryMapCollision(AEVec2& pos, AEVec2& velocity)
{
	int flag = 0;
	Hotspot item;

	// creating hotspots
	item.right.point_1 = { pos.x + GRID_SCALE / 2 , pos.y + GRID_SCALE / 4 };
	item.right.point_2 = { pos.x + GRID_SCALE / 2 , pos.y - GRID_SCALE / 4 };

	item.left.point_1 = { pos.x - GRID_SCALE / 2, pos.y + GRID_SCALE / 4 };
	item.left.point_2 = { pos.x - GRID_SCALE / 2, pos.y - GRID_SCALE / 4 };

	item.top.point_1 = { pos.x - GRID_SCALE / 4, pos.y + GRID_SCALE / 2 };
	item.top.point_2 = { pos.x + GRID_SCALE / 4, pos.y + GRID_SCALE / 2 };

	item.bottom.point_1 = { pos.x - GRID_SCALE / 4, pos.y - GRID_SCALE / 2 };
	item.bottom.point_2 = { pos.x + GRID_SCALE / 4, pos.y - GRID_SCALE / 2 };

	// check collision for bottom
	if (GetCellValue((int)item.bottom.point_1.x / GRID_SCALE, (int)item.bottom.point_1.y / GRID_SCALE) ||
		GetCellValue((int)item.bottom.point_2.x / GRID_SCALE, (int)item.bottom.point_2.y / GRID_SCALE))
	{
		flag += COLLISION_BOTTOM;
		velocity.y = 0.0f;
	}

	// check collision for right
	if (GetCellValue((int)item.right.point_1.x / GRID_SCALE, (int)item.right.point_1.y / GRID_SCALE) ||
		GetCellValue((int)item.right.point_2.x / GRID_SCALE, (int)item.right.point_2.y / GRID_SCALE))
	{
		flag += COLLISION_RIGHT;
		velocity.x = 0;
	}

	// check collision for left
	if (GetCellValue((int)item.left.point_1.x / GRID_SCALE, (int)item.left.point_1.y / GRID_SCALE) ||
		GetCellValue((int)item.left.point_2.x / GRID_SCALE, (int)item.left.point_2.y / GRID_SCALE))
	{
		flag += COLLISION_LEFT;
		velocity.x = 0;
	}

	// check collision for top
	if (GetCellValue((int)item.top.point_1.x / GRID_SCALE, (int)item.top.point_1.y / GRID_SCALE) ||
		GetCellValue((int)item.top.point_2.x / GRID_SCALE, (int)item.top.point_2.y / GRID_SCALE))
	{
		flag += COLLISION_TOP;
		velocity = { 0.0f, -0.01f };
	}

	// return collision flag
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
	// static collision
	if (point1.x > aabb2.min.x &&
		point1.x < aabb2.max.x &&
		point1.y > aabb2.min.y &&
		point1.y < aabb2.max.y)
	{
		return true;
	}

	return false;
}

void create_AABB(AABB& aabb, AEVec2 const& pos, float scale_x, float scale_y)
{
	// create AABB points
	aabb.min.x = pos.x - (scale_x / 2);
	aabb.min.y = pos.y - (scale_y / 2);
	aabb.max.x = pos.x + (scale_x / 2);
	aabb.max.y = pos.y + (scale_y / 2);
}
