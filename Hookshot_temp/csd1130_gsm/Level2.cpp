#include "pch.h"

#include "GamestateManager.h"
#include "Level2.h"

std::fstream f_level2;

int Level2_Counter;
int Level2_Lives;

void Level2_Load()
{
	f_level2.open("\Data/Level2_Lives.txt", std::fstream::in);
	f_level2 >> Level2_Lives;
	f_level2.close();

	file << "Level2:Load\n";

}

void Level2_Initialize()
{
	f_level2.open("\Data/Level2_Counter.txt", std::fstream::in);
	f_level2 >> Level2_Counter;
	f_level2.close();

	file << "Level2:Initialize\n";

}

void Level2_Update()
{
	Input_Handle();

	file << "Level2:Update\n";
	Level2_Counter -= 1;
	

	if (Level2_Counter == 0)
	{
		Level2_Lives -= 1;

		if (Level2_Lives == 0)
		{
			next = GS_QUIT;

		}

		if (Level2_Lives > 0)
		{
			next = GS_RESTART;
		}
	}



	




	
}

void Level2_Draw()
{
	file << "Level2:Draw\n";
}

void Level2_Free()
{
	file << "Level2:Free\n";
}

void Level2_Unload()
{
	file << "Level2:Unload\n";
}