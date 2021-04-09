/*!*************************************************************************
****
\file win.h
\par Project: Hookshot
\authors: Tan Wei Wen (100%)
\par DP email:  t.weiwen@digipen.edu
\date 040821

\brief
This file contains all the functions interface for the win state.

\par Copyright: All content � 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

****************************************************************************
***/

#include "pch.h"

/**************************************************************************/
/*!
	Load level
*/
/**************************************************************************/
void win_Load();

/**************************************************************************/
/*!
	Initialize level
*/
/**************************************************************************/
void win_Initialize();

/**************************************************************************/
/*!
	Update level
*/
/**************************************************************************/
void win_Update();

/**************************************************************************/
/*!
	Draw level
*/
/**************************************************************************/
void win_Draw();

/**************************************************************************/
/*!
	Free level
*/
/**************************************************************************/
void win_Free();

/**************************************************************************/
/*!
	Unload level
*/
/**************************************************************************/
void win_Unload();
