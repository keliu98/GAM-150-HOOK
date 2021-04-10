/*!*************************************************************************
****
\file GameStateManager.h
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
This is a header file for handling game states.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

****************************************************************************
***/

#pragma once
#include "pch.h"


/**************************************************************************/
/*!
	Below are variables & function pointers for game state.
*/
/**************************************************************************/
typedef void(*FP)(void);
extern std::fstream file;
extern int current, previous, next;
extern FP fpLoad, fpInitialize, fpUpdate, fpDraw, fpFree, fpUnload;

/**************************************************************************/
/*!
	Initialize game state.
*/
/**************************************************************************/
void GSM_Initialize(int startingState);

/**************************************************************************/
/*!
	Update game state.
*/
/**************************************************************************/
void GSM_Update();