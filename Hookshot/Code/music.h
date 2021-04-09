/*!*************************************************************************
****
\file music.h
\par Project: Hookshot
\authors: Tan Egi (80%)
		  Tan Wei Wen (20%)
\par DP email: egi.tan@digipen.edu
			   t.weiwen@digipen.edu
\date 090421

\brief
This is the header file for the music system.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

****************************************************************************
***/
#pragma once
#include "pch.h"

/**************************************************************************/
/*!
	This function load all the music.
*/
/**************************************************************************/
void music_Load(const char* file);

/**************************************************************************/
/*!
	This function initialaze all variables that will be used in the music
	system.
*/
/**************************************************************************/
void music_Initialize();

/**************************************************************************/
/*!
	This function is used to play or pause the music based on the boolean
	passed in.
*/
/**************************************************************************/
void music_play(bool stopMusic);

/**************************************************************************/
/*!
	This function is used to mute or umute the music based on the boolean
	passed in.
*/
/**************************************************************************/
void music_mute(bool mute);

/**************************************************************************/
/*!
	This function unload all music used.
*/
/**************************************************************************/
void music_Unload();

/**************************************************************************/
/*!
	This function free all music variables used.
*/
/**************************************************************************/
void music_Free();
