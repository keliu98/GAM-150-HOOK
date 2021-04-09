#pragma once
/*!*************************************************************************
****
\file hookshot.h
\par Project: Hookshot
\authors: Tan Wei Wen (100%)
\par DP email:  t.weiwen@digipen.edu
\par Course: CSD 1450
\date 280221

\brief
This file contains the interface for firing a hook inside the game hookshot.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. All
				rights reserved.

****************************************************************************
***/
/**************************************************************************/
/*!
	Function to fire the hook and to tether on the the bg/wall.
*/
/**************************************************************************/
void fire_hook(int cursor_x, int cursor_y);
/**************************************************************************/
/*!
	Function to release the hook and stop firing.
*/
/**************************************************************************/
void release_hook();
/**************************************************************************/
/*!
	Function for transalating the character position to stay within the arc, "pulling it back in". Called in physics.cpp
*/
/**************************************************************************/
void hook_char_pos_update();