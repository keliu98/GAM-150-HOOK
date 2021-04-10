/*!*************************************************************************
****
\file levelUI.h
\par Project: Hookshot
\authors: Tan Wei Wen (90%)
		  Egi Tan (10%)

\par DP email:  t.weiwen@digipen.edu
				egi.tan@digipen.edu

\par Course: CSD 1450
\date 050421

\brief
This file contains the interface for the UI of the game. For example
creating buttons and printing text on to the screen.

\par Copyright: All content ©2021 Digipen Institute of Technology Singapore. All
				rights reserved.

****************************************************************************
***/

#pragma once
#include "pch.h"

/**************************************************************************/
/*!
	Print text onto the screen base on the message, type of font and 
	position.
*/
/**************************************************************************/
void PrintText(char* message, int type, AEVec2 position);

/**************************************************************************/
/*!
	Function to translate buttons so that they can be created based on ratio of the screen.
*/
/**************************************************************************/
void UpdateButton();

/**************************************************************************/
/*!
	For creating/updating the pause menu.
*/
/**************************************************************************/
void UpdatePauseMenu();

/**************************************************************************/
/*!
	Function to switch between the different statesand actions for each button.
*/
/**************************************************************************/
void switchbuttonstate(int state);
