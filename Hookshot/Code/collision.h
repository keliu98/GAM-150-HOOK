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

#ifndef CS230_COLLISION_H_
#define CS230_COLLISION_H_

#include "pch.h"

bool CollisionIntersection_RectRect(const AABB& aabb1, const AEVec2& vel1,
	const AABB& aabb2, const AEVec2& vel2);


#endif // CS230_COLLISION_H_