/*!*************************************************************************
****
\file LoadMap.h
\par Project: Hookshot
\authors: Tan Egi (70%)
		  Tan Wei Wen (30%)
\par DP email: egi.tan@digipen.edu
			   t.weiwen@digipen.edu
\date 090421

\brief
This is the header file for LoadMap.cpp. It contains function that
loads the binary map.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

****************************************************************************
***/

#pragma once
#include "pch.h"

/*The number of horizontal elements*/
static int map_width;

/*The number of vertical elements*/
static int map_height;

/*This will contain all the data of the map, which will be retreived from a file
when the "ImportMapDataFromFile" function is called*/
static int** map_data;

/*This will contain the collision data of the binary map. It will be filled in the
"ImportMapDataFromFile" after filling "MapData". Basically, if an array element
in MapData is 1, it represents a collision cell, any other value is a non-collision
cell*/
static int** binary_collision_array;

/*This variable will contain the flipped map data from map_data.*/
static int** normalize_map_data;


/**************************************************************************/
/*!
	This function import map data from the text file.
*/
/**************************************************************************/
int ImportMapDataFromTxt(const char* FileName);

/**************************************************************************/
/*!
	This function free map data.
*/
/**************************************************************************/
void UnloadMapData(void);

/**************************************************************************/
/*!
	This function print out the binary map and collision map data.
*/
/**************************************************************************/
void PrintRetrievedInformation(void);

/**************************************************************************/
/*!
	This function retrieve value from the map data grid.
*/
/**************************************************************************/
int	GetCellValue(int X, int Y);

/**************************************************************************/
/*!
	This function load the level by initialize variables used.
*/
/**************************************************************************/
void IntializeLevel();

/**************************************************************************/
/*!
	This function check for the win or lose condition for the game so that 
	it can change the level state.
*/
/**************************************************************************/
bool CheckWinLose();
