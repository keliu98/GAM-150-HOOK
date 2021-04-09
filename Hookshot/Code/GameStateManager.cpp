/*!*************************************************************************
****
\file GameStateManager.cpp
\par Project: Hookshot
\authors: Tan Wei Wen (25%)
		  Egi Tan (25%)
		  Liu Ke (25%)
		  Yong Hui (25%)
\par DP email:  t.weiwen@digipen.edu
				egi.tan@digipen.edu
				ke.liu@digipen.edu
				l.yonghui@digipen.edu
\date 020221

\brief
This source file contains the neccessary functions for running the game 
state manager.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

****************************************************************************
***/

#include "pch.h"

// game states
int current = 0, previous = 0, next = 0;

// state function pointers
FP fpLoad = nullptr, fpInitialize = nullptr, fpUpdate = nullptr, fpDraw = nullptr, fpFree = nullptr, fpUnload = nullptr;

std::fstream file;

//Intialise the which state to start in. 
//Param In, the state that should be intialise, refer to GameStateList.h
void GSM_Initialize(int startingState)
{
	current = previous = next = startingState;

}

//Switches the function pointers depending on the current state. To add more cases as we add more states/levels
void GSM_Update()
{
	switch (current)
	{
		case GS_MENU:
			fpLoad = menu_Load;
			fpInitialize = menu_Initialize;
			fpUpdate = menu_Update;
			fpDraw = menu_Draw;
			fpFree = menu_Free;
			fpUnload = menu_Unload;
			break;
		case GS_INTRO:
			fpLoad = intro_Load;
			fpInitialize = intro_Initialize;
			fpUpdate = intro_Update;
			fpDraw = intro_Draw;
			fpFree = intro_Free;
			fpUnload = intro_Unload;
			break;
		case GS_LEVEL1:		
			fpLoad = Level1_Load;
			fpInitialize = Level1_Initialize;
			fpUpdate = Level1_Update;
			fpDraw = Level1_Draw;
			fpFree = Level1_Free;
			fpUnload = Level1_Unload;
			break;
		case GS_LEVEL2:
			fpLoad = Level2_Load;
			fpInitialize = Level2_Initialize;
			fpUpdate = Level2_Update;
			fpDraw = Level2_Draw;
			fpFree = Level2_Free;
			fpUnload = Level2_Unload;
			break;
		case GS_LEVEL3:
			fpLoad = Level3_Load;
			fpInitialize = Level3_Initialize;
			fpUpdate = Level3_Update;
			fpDraw = Level3_Draw;
			fpFree = Level3_Free;
			fpUnload = Level3_Unload;
			break;
		case GS_LEVEL4:
			fpLoad = Level4_Load;
			fpInitialize = Level4_Initialize;
			fpUpdate = Level4_Update;
			fpDraw = Level4_Draw;
			fpFree = Level4_Free;
			fpUnload = Level4_Unload;
			break;
		case GS_LEVEL5:
			fpLoad = Level5_Load;
			fpInitialize = Level5_Initialize;
			fpUpdate = Level5_Update;
			fpDraw = Level5_Draw;
			fpFree = Level5_Free;
			fpUnload = Level5_Unload;
			break;
		case GS_WIN:
			fpLoad = win_Load;
			fpInitialize = win_Initialize;
			fpUpdate = win_Update;
			fpDraw = win_Draw;
			fpFree = win_Free;
			fpUnload = win_Unload;
			break;
		case GS_RESTART:
			break;
		case GS_QUIT:
			break;
		default:
			break;
	}
}