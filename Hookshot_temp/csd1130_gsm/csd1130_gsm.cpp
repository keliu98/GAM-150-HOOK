/*!*************************************************************************
****
\file csd1130_gsm.cpp
\author Tan Wei Wen
\par DP email: t.weiwen@digipen.edu
\par Course: CS1130
\par Project: Project_1_Part_2
\date 270121


\brief
  This source file contains the main function that executes the the neccessary functions for running the game state manager.

  The functions include:
  - main
    The entry point of the program

****************************************************************************
***/

// cs230_gsm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include "GameStateManager.h"
#include "System.h""

//Implement the pseudo-code of A1_P1 here
int main()
{
    System_Intialize();

    //GSM initialize
    GSM_Initialize(GS_LEVEL1);

    while (current != GS_QUIT)
    {
        //Set state to previous if it is restarted.
        if (current == GS_RESTART)
        {
            current = previous;
            next = previous;
        }
        else
        {
            //If it is not restarting or quiting -> AKA Level Change -> Calls the GSM_Update, to update the function pointers
            GSM_Update();
            fpLoad();
        }

        fpInitialize();

        //Gameplay Loop
        //**Need to add frames in actual build
        while (current == next)
        {
            fpUpdate();
            fpDraw();
        
        }

        //Out of the loop = Quit, Restart, Change level
        fpFree();

        if (next != GS_RESTART)
        {
            fpUnload();
        }

        previous = current;
        current = next;
    }
    

    //Systems exit (terminate)
    System_Exit();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
