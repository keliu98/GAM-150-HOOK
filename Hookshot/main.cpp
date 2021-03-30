
/*!*************************************************************************
****
\file GameStateManager.cpp
\authors: Tan Wei Wen
		  Egi Tan
		  Liu Ke
		  Yong Hui

\par DP email:  t.weiwen@digipen.edu
				egi.tan@digipen.edu
				ke.liu@digipen.edu
				l.yonghui@digipen.edu

\par Course: CSD 1450
\par Project: Software Engineering Project 2
\date 020221


\brief //TODO


****************************************************************************
***/

// ---------------------------------------------------------------------------
// includes

#include "Code/pch.h"

/*
	NOTES:
		mesh - shapes of objects. Eg: circle, square, triangle
			 - colour / texture 
*/
// ---------------------------------------------------------------------------
// main

float	 g_dt;
double	 g_appTime;
int      WINDOW_WIDTH = 800;
int      WINDOW_HEIGHT = 600;
size_t   TOTAL_LIVES = 3;
char	 font;
char	 font_italic;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif
	 //int * pi = new int;

	//Intialise System
	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, WINDOW_WIDTH, WINDOW_HEIGHT, 1, 60, true, NULL);

	// init font id:
	font = AEGfxCreateFont("../Fonts/Pixel Digivolve.otf", 24);
	font_italic = AEGfxCreateFont("../Fonts/Pixel Digivolve Italic.otf", 16);

	// Changing the window title
	AESysSetWindowTitle("Hookshot");

	// reset the system modules
	AESysReset();

	//set background color
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

    //GSM initialize
    GSM_Initialize(GS_MENU);

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
			// Informing the system about the loop's start
			AESysFrameStart();

            fpUpdate();
            fpDraw();

			// Informing the system about the loop's end
			AESysFrameEnd();
        
			g_dt = (f32)AEFrameRateControllerGetFrameTime();

			if (0 == AESysDoesWindowExist())
				next = GS_QUIT;

		/*	while (g_dt < 0.16667f)
			{
				g_dt += g_dt;
			}*/

			if (g_dt > 0.166667f)
				g_dt = 0.166667f;
			
			g_appTime += g_dt;
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
    
	// Destory font ID
	AEGfxDestroyFont(font);
	AEGfxDestroyFont(font_italic);

	// free the system
	AESysExit();

}
