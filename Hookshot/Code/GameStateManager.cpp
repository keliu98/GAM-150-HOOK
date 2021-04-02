/*!*************************************************************************
****
\file GameStateManager.cpp
\authors: Tan Wei Wen
		  Egi Tan
		  Liu Ke
		  Yong Hui

\par DP email:  t.weiwen@digipen.edu
				egi.tan@digipen.edu
				ke.liu@digipen.edu
				l.yonghui@digipen.edu
				
\par Course: CSD 1450
\par Project: Software Engineering Project 2
\date 020221


\brief
  This source file contains the neccessary functions for running the game state manager.

	The functions includes:
	- GSM_Initialize:
		Intialise the which state to start in.

	-GSM_Update
		Switches the function pointers depending on the current state
		

****************************************************************************
***/

#include "pch.h"

int current = 0, previous = 0, next = 0;

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
	case GS_RESTART:
		break;
	case GS_QUIT:
		break;
	default:
		break;
	}
}