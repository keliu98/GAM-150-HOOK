#include "pch.h"

#include "GamestateManager.h"

int Level1_Counter;

void Level1_Load()
{
	std::fstream f_level1;
	f_level1.open("\Data/Level1_Counter.txt", std::fstream::in);
	f_level1 >> Level1_Counter;
	f_level1.close();

	file << "Level1:Load\n";
}

void Level1_Initialize()
{
	file << "Level1:Initialize\n";
}

void Level1_Update()
{
	Input_Handle();
	Level1_Counter -= 1;

	file << "Level1:Update\n";

	if (Level1_Counter == 0)
	{
		next = GS_LEVEL2;
	}
}

void Level1_Draw()
{
	file << "Level1:Draw\n";
}

void Level1_Free()
{
	file << "Level1:Free\n";
}

void Level1_Unload()
{
	file << "Level1:Unload\n";
}