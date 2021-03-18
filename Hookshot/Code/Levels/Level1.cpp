#include "../pch.h"

void Level1_Load()
{
	//../Code/Levels/Exported.txt
	if (ImportMapDataFromTxt("../Levels/Level_1.txt"))
	{
		// For debugging map binary data
		// PrintRetrievedInformation();
	}
	else
	{
		next = GS_QUIT;
	}

	//loading texture etc
	load_render();

	// loading wall texture
	load_dirt_render();

	// loading character texture
	load_character_render();

	// load enemy_texture
	load_enemy_texture();

	// load hook_texture
	load_hook_render();

	if (TOTAL_LIVES <= 0) {
		TOTAL_LIVES = 3;
	}
}

void Level1_Initialize()
{
	//Translate the map data into the gameworld by creating objects
	IntializeLevel();

	//Intialize camera
	camera_init(character->pos);

	//Intialise physic
	physics_intialize();

}

void Level1_Update()
{

	// Handling Input
	AEInputUpdate();
	Input_g_mode();

	//Updating the physics of the game e.g acceleration, velocity, gravity
	physics_update();

	// Updating the Collision
	UpdateCollision();

	camera_update(character->pos, character->velocity, character->scale);
	//For Debuging Camera
	//draw_static_obj();
	AEVec2 dir = { -1.0f, 0.0f };
	//enermy AI
	for (size_t i =0;i< enemies.size(); i++)
	{
		
		set_vel_to_pos(enemies[i].pos, enemies[i].velocity);

		//Gravity.
		set_accel_to_vel(enemies[i].velocity, dir, 200.0f);

		//Horizontal Friction. 
		//enemy.velocity.x = enemy.velocity.x * 0.97f;

		//!!!!!!!!!!!!!!!! Temporary wall collision NEED TO CHANGE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
	}
		//draw_static_obj();

	CheckWinLose();
}

void Level1_Draw()
{
	update_render_walls();
	update_render_hook();
	update_render_enemy();
	update_render_character();

	//For Debuging Camera
	draw_cam_bounding_box(character->pos, character->pos);

	// debugging hotspot
	/*draw_cam_bounding_box({ character->pos.x + character->scale / 4, character->pos.y - character->scale / 2 },
		{ character->pos.x - character->scale / 4, character->pos.y + character->scale / 2 });*/

	//Temporary for exiting the system
	if (AEInputCheckTriggered(AEVK_ESCAPE))
		next = GS_QUIT;
}

// Called if change state, for everything including reset
void Level1_Free()
{
	free_objects();
}

//  Called if change state and State is NOT reset. ie Change levels. Do not unload if reseting.
void Level1_Unload()
{
	FreeMapData();
	unload_render();
}