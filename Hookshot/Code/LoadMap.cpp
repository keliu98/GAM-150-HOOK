/******************************************************************************/
/*!
\file         LoadMap.cpp
\author       Tan Egi, egi.tan, 2002777
\par          egi.tan@digipen.edu
\date         March 4, 2021
\brief        This file loads the binary map and collision map.It also free, 
			  print and retrieve data from the map.

Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior 
written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/
#include "LoadMap.h"


int ImportMapDataFromTxt(const char* FileName)
{
	std::ifstream read_file;
	std::string file_input;

	read_file.open(FileName);
	if (read_file)
	{
		std::getline(read_file, file_input);
		map_width = std::stoi(file_input.substr(file_input.find_first_of(" ")));

		std::getline(read_file, file_input);
		map_height = std::stoi(file_input.substr(file_input.find_first_of(" ")));

		map_data = new int* [map_height];
		binary_collision_array = new int* [map_height];
		normalize_map_data = new int* [map_height];

		for (int x = 0; x < map_height; ++x)
		{
			map_data[x] = new int[map_width];
			binary_collision_array[x] = new int[map_width];
			normalize_map_data[x] = new int[map_width];
		}
		

		char c;
		int x1 = map_height - 1;
		for (int x = 0; x < map_height; ++x)
		{
			for (int y = 0; y < map_width; ++y)
			{
				read_file >> c;
				if (isdigit(c))
				{
					map_data[x][y] = (int)c - 48;
					binary_collision_array[x1][y] = map_data[x][y];
					normalize_map_data[x1][y] = map_data[x][y];

					if (map_data[x][y] != 1)
					{
						binary_collision_array[x1][y] = 0;
					}
					// std::cout << "Map["<< x << ", " << y << "]:" << map_data[x][y] << " | ";
				}
				else
				{
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

void FreeMapData(void)
{
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
	std::cout << "NORM Map: " << map_width << " x " << map_height << std::endl;

	for (int x = 0; x < map_height; ++x)
	{
		for (int y = 0; y < map_width; ++y)
		{
			std::cout << normalize_map_data[x][y] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "Map: " << map_width << " x " << map_height << std::endl;

	for (int x = 0; x < map_height; ++x)
	{
		for (int y = 0; y < map_width; ++y)
		{
			std::cout << map_data[x][y] << " ";
		}
		std::cout << std::endl;
	}

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

/*int	GetCellValue(int X, int Y)
{
	// Check within
	if ((X >= 0 && X < map_width) && ((Y >= 0 && Y < map_height)))
	{
		return binary_collision_array[Y][X];
	}

	return 0;
}*/

int GetCellValue(int X, int Y)
{
	if (X > (map_width - 1) || X<0 || Y >(map_height - 1) || Y < 0) {//if value is out of bound return 0
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

	AEVec2 init_pos = pos;
	for (int x = 0; x < map_height; ++x)
	{
		// std::cout << x << " | ";
		for (int y = 0; y < map_width; ++y)
		{
			// type 1 = wall
			if (normalize_map_data[x][y] == 1)
			{
				create_wall(TEMP_WALL, 40, pos);
			}
			// type 2 = character
			if (normalize_map_data[x][y] == 'C')
			{
				character = create_character(pos);
				//create_AABB(character->aabb, character->pos, character->scale);
				hook = create_hook();
			}
			// type 3 = enemy
			if (normalize_map_data[x][y] == 'E')
			{
				create_enemy(TEMP_ENEMY, pos);
			}
			// Ending point
			if (normalize_map_data[x][y] == 2)
			{
				end_position = create_ending_point(pos);
			}
			pos.x += (wall_scale * 2);
		}
		pos.y += (wall_scale * 2);
		pos.x = init_pos.x;
	}

	walls.shrink_to_fit();

	std::cout << walls.size() << '\n';
	std::cout << walls.capacity() << '\n';
}

void CheckWinLose()
{
	// ending position is always top right, so will need to caculate bottom left
	if (character->pos.x <= end_position->x && character->pos.x >= (end_position->x - 40 * 4) &&
		character->pos.y <= end_position->y && character->pos.y >= (end_position->y - 40 * 4))
	{
		//TO CHANGE TO NEXT LEVEL
		next = GS_RESTART;
	}

	//TODO when character->pos.y < map_height * grid , --lives 
	if (0)
	{

	}

	if (lives == 0)
	{
		//TO CHANGE TO GAMEOVER, Lives is intialised when game is started. Do not declare lives in load or intialise as it will get reseted.
		lives = 3;
		next = GS_RESTART;
		
	}
	//if (character->pos.y <  )
}


