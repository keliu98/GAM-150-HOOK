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

/**************************************************************************/
/*!
	A collision test function to see if two rectangle object collide together.
*/
/**************************************************************************/
bool CollisionIntersection_RectRect(const struct AABB& aabb1, const AEVec2& vel1, const struct AABB& aabb2, const AEVec2& vel2);
