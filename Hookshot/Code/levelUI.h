/*!*************************************************************************
****
\file levelUI.h
\par Project: Hookshot
\authors: Tan Wei Wen (75%)
		  Tan Egi (25%)
\par DP email: t.weiwen@digipen.edu
			   egi.tan@digipen.edu
\date 090421

\brief
This is a header file containing functions that handle all the UI in the
game.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

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

void UpdateButton();
void UpdatePauseMenu();
void switchbuttonstate(int state);
