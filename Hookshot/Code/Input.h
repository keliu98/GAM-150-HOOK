/*!*************************************************************************
****
\file input.cpp
\par Project: Hookshot
\authors: Yong Hui (80%)
		  Tan Wei Wen (15%)
		  Egi Tan (5%)

\par DP email: l.yonghui@digipen.edu
			   t.weiwen@digipen.edu
			   egi.tan@digipen.edu

\par Course: CSD 1450
\date 090421

\brief
This file contain the interface for the input of the game and menu. Functions
are to be called by the game state.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore.
				All rights reserved.

****************************************************************************
***/

#pragma once
#include "pch.h"

/**************************************************************************/
/*!
	Skip the introduction screen for logo.
*/
/**************************************************************************/
void skip_intro();

/**************************************************************************/
/*!
	Check for input during game.
*/
/**************************************************************************/
void Input_g_mode();

/**************************************************************************/
/*!
	Check for input when at main menu
*/
/**************************************************************************/
void Input_menu_mode();

/**************************************************************************/
/*!
	Check if window is minimized
*/
/**************************************************************************/
bool check_minimized_window();
