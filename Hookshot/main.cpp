// ---------------------------------------------------------------------------
// includes

#include "AEEngine.h"
#include "testrender.h"

/*
	NOTES:
		mesh - shapes of objects. Eg: circle, square, triangle
			 - colour / texture 
*/
// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	///////////////////////
	// Variable declaration

	int gGameRunning = 1;

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 800, 600, 1, 60, true, NULL);


	// Changing the window title
	AESysSetWindowTitle("Hookshot");

	// reset the system modules
	AESysReset();

	//set background color
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);

	// Initialization end
	/////////////////////

	GameObj item = load_render("bug1.png");
	AEVec2 test_pos = { 100.0f, -60.0f };
	draw_render1(test_pos, item.pMesh1, item.pTex);
	free_render(item.pMesh1, item.pTex);

	// free the system
	AESysExit();

}