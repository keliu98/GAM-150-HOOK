/*!*************************************************************************
****
\file GameStateList.h
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
\date 080421


\brief
  This source file contains all the game states. 

****************************************************************************
***/
#pragma once

/**************************************************************************/
/*!
	Below are all the game state.
*/
/**************************************************************************/
enum GS_STATES
{
	GS_INTRO,
	GS_MENU,
	GS_LEVEL1,
	GS_LEVEL2,
	GS_LEVEL3,
	GS_LEVEL4,
	GS_LEVEL5,

	GS_WIN,
	
	GS_QUIT,
	GS_RESTART,

	GS_NONE
};