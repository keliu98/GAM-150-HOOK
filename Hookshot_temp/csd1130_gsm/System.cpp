#include "pch.h"

#include "System.h"
#include "GameStateManager.h"

void System_Intialize()
{
	file.open("\Data/Output.txt", std::fstream::app);
	file << "System:Initialize\n";

}

void System_Exit()
{
	file << "System:Exit\n";
	file.close();
}