/*!*************************************************************************
****
\file win.cpp
\par Project: Hookshot
\authors: Tan Wei Wen (100%)

\par DP email:  t.weiwen@digipen.edu

\par Course: CSD 1450
\date 050421

\brief
This file contains the interface for the win state of the game. Displays the
game win screen. To be used by game state manager

\par Copyright: All content ©2021 Digipen Institute of Technology Singapore. All
				rights reserved.

****************************************************************************
***/

#include "pch.h"

/**************************************************************************/
/*!
	Load win_state - Load Assets
*/
/**************************************************************************/
void win_Load();

/**************************************************************************/
/*!
	Initialize win_state - Intialise Variables
*/
/**************************************************************************/
void win_Initialize();

/**************************************************************************/
/*!
	Update win_state - Interaction with win state
*/
/**************************************************************************/
void win_Update();

/**************************************************************************/
/*!
	Draw win_state - Credits, Bg, buttons, fonts
*/
/**************************************************************************/
void win_Draw();

/**************************************************************************/
/*!
	Free win_state - Free any music and buttons
*/
/**************************************************************************/
void win_Free();

/**************************************************************************/
/*!
	Unload win_state - Unload Assets
*/
/**************************************************************************/
void win_Unload();
