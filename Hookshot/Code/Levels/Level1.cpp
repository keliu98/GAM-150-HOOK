#include "../pch.h"

const unsigned int	GAME_OBJ_INST_NUM_MAX = 2048;	//The total number of different game object instances


//Declaration of Variables.
AEGfxVertexList* pMesh1 = 0;
int Flag;
static bool game_end;

void Level1_Load()
{
	//../Code/Levels/Exported.txt
	if (ImportMapDataFromTxt("../Levels/Level_1.txt"))
	{
		// For debugging map binary data
		// PrintRetrievedInformation();
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

}

void Level1_Initialize()
{
	//Translate the map data into the gameworld by creating objects
	IntializeLevel();

	//Intialize camera
	camera_init(character->pos);

	//Intialise physic
	physics_intialize();

	game_end = false;
	
}

void Level1_Update()
{
	if (!game_end)
	{
		Flag = CheckInstanceBinaryMapCollision(character->pos, character->velocity);
		for (Enemy& enemy : enemies)
			CheckInstanceBinaryMapCollision(enemy.pos, enemy.velocity);

		// Handling Input
		AEInputUpdate();
		Input_g_mode(Flag);

		//Updating the physics of the game e.g acceleration, velocity, gravity
		physics_update(Flag);

		camera_update(character->pos, character->velocity, character->scale);
		//For Debuging Camera
		//draw_static_obj();


		//if (Flag == COLLISION_BOTTOM)
		//{
		//	SnapToCell(&character->pos.y);
		//	character->velocity.y = 0;
		//	Flag -= COLLISION_BOTTOM;
		//	printf("BOTTOM POS: %f, %f\n", character->pos.x, character->pos.y);
		//}

		// ending position is always top right, so will need to caculate bottom left
		if (character->pos.x <= end_position->x && character->pos.x >= (end_position->x - 40 * 4) &&
			character->pos.y <= end_position->y && character->pos.y >= (end_position->y - 40 * 4))
		{
			game_end = true;
		}
	}

	else
	{
		// For now character will not be able to move.
		// show end screen or next lvl

	}
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