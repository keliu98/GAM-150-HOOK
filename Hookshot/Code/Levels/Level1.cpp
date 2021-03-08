#include "../pch.h"

//Declaration of Variables.
AEGfxVertexList* pMesh1 = 0;


void Level1_Load()
{
	//loading the map data from text file
	if (ImportMapDataFromTxt("../Code/Levels/Map_1.txt"))
	{
		PrintRetrievedInformation();
	}

	//loading texture etc
	load_render();
}

void Level1_Initialize()
{
	//Translate the map data into the gameworld by creating objects
	IntializeLevel();

	//Intialise physic
	physics_intialize();

	//Intialize camera
	camera_init(character->pos);

}

void Level1_Update()
{
	float delta_time = g_dt;

	// Handling Input
	AEInputUpdate();
	Input_g_mode();
	
	//Updating the physics of the game e.g acceleration, velocity, gravity
	physics_update();

	camera_update(character->pos, character->velocity, character->scale);
		//For Debuging Camera
		//draw_cam_bounding_box();
		//draw_static_obj();

	
}

void Level1_Draw()
{
	update_render_walls();
	update_render_character();
	update_render_hook();


	//Temporary for exiting the system
	if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
		next = GS_QUIT;
}

// Called if change state, for everything including reset
void Level1_Free()
{
	FreeMapData();
	free_object(character, hook, walls);
}

//  Called if change state and State is NOT reset. ie Change levels. Do not unload if reseting.
void Level1_Unload()
{
	unload_render();
}