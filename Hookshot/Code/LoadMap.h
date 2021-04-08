/******************************************************************************/
/*!
\file         LoadMap.h
\author       Tan Egi, egi.tan, 2002777
\par          egi.tan@digipen.edu
\date         March 4, 2021
\brief        This is the header file for LoadMap.cpp. It contains function that
			  loads the binary map.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior 
written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/
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

static int** normalize_map_data;

// import map from text file
int ImportMapDataFromTxt(const char* FileName);

// free map data
void UnloadMapData(void);

// print binary map and collision map
void PrintRetrievedInformation(void);

// retrieve value from cell
int	GetCellValue(int X, int Y);

//loading of the level
void IntializeLevel();

//Checking for win or lose or level change state
void CheckWinLose();


// std::vector<Wall*> loadLevel();