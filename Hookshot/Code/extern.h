/*!*************************************************************************
****
\file extern.h
\par Project: Hookshot
\authors: Tan Wei Wen (25%)
		  Egi Tan (25%)
		  Liu Ke (25%)
		  Yong Hui (25%)
\par DP email:  t.weiwen@digipen.edu
				egi.tan@digipen.edu
				ke.liu@digipen.edu
				l.yonghui@digipen.edu
\date 080421

\brief
This source file contains all global variables for the game.

\par Copyright: All content � 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

****************************************************************************
***/

#pragma once

#include "pch.h"

/**************************************************************************/
/*!
	Below are globals variables for the program.
*/
/**************************************************************************/
extern float	g_dt;
extern double	g_appTime;

extern int      WINDOW_HEIGHT;
extern int      WINDOW_WIDTH;

/**************************************************************************/
/*!
	Global variables for Physics
*/
/**************************************************************************/
extern float    CHAR_HEIGHT_VEL;
extern const float GRAVITY;

/**************************************************************************/
/*!
	Global variables for Fonts
*/
/**************************************************************************/
extern char		font;
extern char		font_italic;
extern char		smaller_font;

/**************************************************************************/
/*!
	Global variables for checking if game is paused and if to display 
	credits.
*/
/**************************************************************************/
extern bool PAUSE;
extern bool sound_mute;
extern bool display_credits;
extern bool display_tutorial;
extern bool confirm_state;
extern int guidePage;
extern int creditsPage;

/**************************************************************************/
/*!
	Global variables for buttons
*/
/**************************************************************************/
//spacing to make it easier when arranging buttons
extern const float BUTTONSPACE_Y; 

//The different states
extern const int MENU;
extern const int CONFIRM_QUIT; 
extern const int FULLSCREEN;
extern const int SOUND;
extern const int TUTORIAL;
extern const int LEVELSELECT;
extern const int CREDITS;
extern const int OPTIONS;

/**************************************************************************/
/*!
	Global variables for collision
*/
/**************************************************************************/
extern const int GRID_SCALE;


