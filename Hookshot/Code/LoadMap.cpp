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

		for (int x = 0; x < map_height; ++x)
		{
			map_data[x] = new int[map_width];
			binary_collision_array[x] = new int[map_width];
		}


		char c;
		for (int x = 0; x < map_height; ++x)
		{
			for (int y = 0; y < map_width; ++y)
			{
				read_file >> c;
				if (isdigit(c))
				{
					map_data[x][y] = (int)c - 48;
					binary_collision_array[x][y] = map_data[x][y];

					if (map_data[x][y] != 1)
					{
						binary_collision_array[x][y] = 0;
					}
					// std::cout << "Map["<< x << ", " << y << "]:" << map_data[x][y] << " | ";
				}
			}
			// std::cout << "\n";
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
		}
	}

	free(map_data);
	free(binary_collision_array);
}

void PrintRetrievedInformation(void)
{
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

int	GetCellValue(int X, int Y)
{
	// Check within
	if ((X >= 0 && X < map_width) && ((Y >= 0 && Y < map_height)))
	{
		return binary_collision_array[Y][X];
	}

	return 0;
}

//WEI WEN: We will need to change this to intialse level, so that we can reset the positions of all the characters ?
void IntializeLevel()
{
	float wall_scale = 20.0f;
	AEVec2 wall_pos = { AEGfxGetWinMinX() + wall_scale, AEGfxGetWinMinY() + wall_scale }; // store bottom left of the position

	AEVec2 init_pos = wall_pos;
	for (int x = 0; x < map_height; ++x)
	{
		// std::cout << x << " | ";
		for (int y = 0; y < map_width; ++y)
		{
			if (binary_collision_array[x][y] == 1)
			{
				create_wall(TEMP_WALL, wall_scale * 2, wall_pos);
			}

			wall_pos.x += (wall_scale * 2);
		}
		wall_pos.y += (wall_scale * 2);
		wall_pos.x = init_pos.x;
	}

	//WEI WEN: Egi need ya to translate the position of where the character is on the map data into the creating the characters at the specific spot. Probably need to change it so that
	//the function create character takes in the position. 
	character = create_character();
	hook = create_hook();
	create_enemy(TEMP_ENEMY, {0.0f, 0.0f});
}


