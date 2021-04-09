/*!*************************************************************************
****
\file win.h
\authors: Tan Wei Wen

\par DP email:  t.weiwen@digipen.edu

\par Course: CSD 1450
\par Project: Software Engineering Project 2
\date 040821


\brief
  This file contains all the functions interface for the win state.
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
