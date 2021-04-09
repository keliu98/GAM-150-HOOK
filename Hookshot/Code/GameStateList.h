/*!*************************************************************************
****
\file GameStateList.h
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
This source file contains all the game states. 

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

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