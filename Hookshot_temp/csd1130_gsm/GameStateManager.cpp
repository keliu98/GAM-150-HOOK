/*!*************************************************************************
****
\file GameStateManager.cpp
\author Tan Wei Wen
\par DP email: t.weiwen@digipen.edu
\par Course: CS1130
\par Project: Project_1_Part_2
\date 270121


\brief
  This source file contains the main function that executes the the neccessary functions for running the game state manager.

	The functions includes:
	- GSM_Initialize:
		Intialise the which state to start in.

	-GSM_Update
		Switches the function pointers depending on the current state
		

****************************************************************************
***/

#include "pch.h"

#include "GameStateManager.h"
#include "Level1.h"
#include "Level2.h"

int current = 0, previous = 0, next = 0;

FP fpLoad = nullptr, fpInitialize = nullptr, fpUpdate = nullptr, fpDraw = nullptr, fpFree = nullptr, fpUnload = nullptr;

std::fstream file;

//Intialise the which state to start in. 
//Param In, the state that should be intialise, refer to GameStateList.h
void GSM_Initialize(int startingState)
{
	current = previous = next = startingState;
	file << "GSM:Initialize\n";


}

//Switches the function pointers depending on the current state
void GSM_Update()
{
	file << "GSM:Update\n";

	switch (current)
	{
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