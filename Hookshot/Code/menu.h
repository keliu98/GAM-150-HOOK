/*!*************************************************************************
****
\file menu.h
\par Project: Hookshot
\authors: Tan Wei Wen (90%)
		  Egi Tan (10%)

\par DP email:  t.weiwen@digipen.edu
				egi.tan@digipen.edu

\par Course: CSD 1450
\date 050421

\brief
This file contains the interface for the menu state of the game. 
To be used by the game state manager.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. All
				rights reserved.

****************************************************************************
***/

#pragma once

extern int guidePage;

/**************************************************************************/
/*!
	Load Menu - Mostly render and music
*/
/**************************************************************************/
void menu_Load();
/**************************************************************************/
/*!
	Initialize Menu - Creations of buttons and Intialise checks.
*/
/**************************************************************************/
void menu_Initialize();
/**************************************************************************/
/*!
	Update Menu - Input and Button interaction
*/
/**************************************************************************/
void menu_Update();
/**************************************************************************/
/*!
	Draw level - Draw Bg and Buttons
*/
/**************************************************************************/
void menu_Draw();
/**************************************************************************/
/*!
	Free Menu - Free music and buttons
*/
/**************************************************************************/
void menu_Free();
/**************************************************************************/
/*!
	Unload Menu - Unload textures and music
*/
/**************************************************************************/
void menu_Unload();
