/*!*************************************************************************
****
\file LoadMap.cpp
\par Project: Hookshot
\authors: Tan Egi (70%)
		  Tan Wei Wen (30%)

\par DP email: egi.tan@digipen.edu
			   t.weiwen@digipen.edu
\date 090421

\brief
This file loads the binary map and collision map.It also free, print and 
retrieve data from the map.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

****************************************************************************
***/

#include "LoadMap.h"


int ImportMapDataFromTxt(const char* FileName)
{
	std::ifstream read_file;
	std::string file_input;

	read_file.open(FileName);
	if (read_file)
	{
		// read width
		std::getline(read_file, file_input);
		map_width = std::stoi(file_input.substr(file_input.find_first_of(" ")));

		// read height
		std::getline(read_file, file_input);
		map_height = std::stoi(file_input.substr(file_input.find_first_of(" ")));

		// create height space for all map arrays
		map_data = new int* [map_height];
		binary_collision_array = new int* [map_height];
		normalize_map_data = new int* [map_height];

		// create width space
		for (int x = 0; x < map_height; ++x)
		{
			map_data[x] = new int[map_width];
			binary_collision_array[x] = new int[map_width];
			normalize_map_data[x] = new int[map_width];
		}
		
		// store each map data from file to array
		char c;
		int x1 = map_height - 1;
		for (int x = 0; x < map_height; ++x)
		{
			for (int y = 0; y < map_width; ++y)
			{
				read_file >> c;
				if (isdigit(c))
				{
					// store map data - this is for letters
					map_data[x][y] = (int)c - 48;
					binary_collision_array[x1][y] = map_data[x][y];
					normalize_map_data[x1][y] = map_data[x][y];
					if (map_data[x][y] != 1)
					{
						binary_collision_array[x1][y] = 0;
					}
				}
				else
				{
					// store map data - this is for normal numbers
					map_data[x][y] = (int)c;
					binary_collision_array[x1][y] = map_data[x][y];
					normalize_map_data[x1][y] = map_data[x][y];

					if (map_data[x][y] != 1)
					{
						binary_collision_array[x1][y] = 0;
					}
				}
			}
			--x1;
		}

		read_file.close();
		return 1;
	}
	return 0;
}

void UnloadMapData(void)
{
	// free all array
	for (int i = 0; i < map_height; ++i)
	{
		if (map_data)
		{
			free(map_data[i]);
			free(binary_collision_array[i]);
			free(normalize_map_data[i]);
		}
	}

	free(map_data);
	free(binary_collision_array);
	free(normalize_map_data);
}

void PrintRetrievedInformation(void)
{
	// print normal map data
	std::cout << "NORM Map: " << map_width << " x " << map_height << std::endl;

	for (int x = 0; x < map_height; ++x)
	{
		for (int y = 0; y < map_width; ++y)
		{
			std::cout << normalize_map_data[x][y] << " ";
		}
		std::cout << std::endl;
	}

	// print map data
	std::cout << "Map: " << map_width << " x " << map_height << std::endl;

	for (int x = 0; x < map_height; ++x)
	{
		for (int y = 0; y < map_width; ++y)
		{
			std::cout << map_data[x][y] << " ";
		}
		std::cout << std::endl;
	}

	// print collision data
	std::cout << std::endl << "Collision Map:" << std::endl;

	for (int x = 0; x < map_height; ++x)
	{
		// std::cout << x << " | ";
		for (int y = 0; y < map_width; ++y)
		{
			std::cout << binary_collision_array[x][y] << " ";
		}
		std::cout << std::endl;
	}
}

int GetCellValue(int X, int Y)
{
	if (X > (map_width - 1) || X<0 || Y >(map_height - 1) || Y < 0) { //if value is out of bound return 0
		return 0;
	}
	else {
		 return binary_collision_array[Y][X]; //else return the Value of the collision
	}
}

void IntializeLevel()
{
	float wall_scale = 20.0f;
	AEVec2 pos = { wall_scale,  wall_scale }; // store bottom left of the position
	int check_x = 0;

	AEVec2 init_pos = pos;
	for (int x = 0; x < map_height; ++x)
	{
		for (int y = 0; y < map_width; ++y)
		{
			// wall
			if (normalize_map_data[x][y] == 1)
			{
				check_x = x + 1;

				// check if it is top
				if (check_x < map_height && normalize_map_data[check_x][y] != 1)
				{
					create_wall(1, 40, pos); // top wall
				}
					
				else
					create_wall(2, 40, pos); // bottom wall
			}

			// character
			if (normalize_map_data[x][y] == 'C')
			{
				character = create_character(pos);
				hook = create_hook();
			}

			// enemy
			if (normalize_map_data[x][y] == 'E')
			{
				create_enemy(TEMP_ENEMY, pos);
			}

			// Ending point
			if (normalize_map_data[x][y] == 2)
			{
				end_position = create_ending_point(pos);
			}

			// spikes
			if (normalize_map_data[x][y] == 'S')
			{
				create_spikes(40, pos);
			}

			pos.x += (wall_scale * 2);
		}
		pos.y += (wall_scale * 2);
		pos.x = init_pos.x;
	}

	AE_ASSERT_MESG(character, "Character is not created [NULL]");
	AE_ASSERT_MESG(end_position, "Goal is not created [NULL]");

	walls.shrink_to_fit();
	enemies.shrink_to_fit();
}

bool CheckWinLose()
{	
	// REACHING THE GOAL
	// ending position is always top right, so will need to caculate bottom left
	if (character->pos.x <= end_position->x && character->pos.x >= (end_position->x - 40 * 4) &&
		character->pos.y <= end_position->y && character->pos.y >= (end_position->y - 40 * 4))
	{
		next++;
		return true;
	}

	//HEATH REDUCED TO ZERO
	if (character->health == 0)
	{
		lives --; //reduce lives
		next = GS_RESTART; //restart level
	}

	//LIVES REDUCED TO ZERO
	if (lives == 0)
	{
		// Lives is intialised when game is started. Do not declare lives in load or intialise as it will get reseted.
		lives = 3; //reset lives
		next = GS_MENU;
	}

	return false;
}

