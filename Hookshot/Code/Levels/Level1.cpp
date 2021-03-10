#include "../pch.h"

const unsigned int	GAME_OBJ_INST_NUM_MAX = 2048;	//The total number of different game object instances


//Declaration of Variables.
AEGfxVertexList* pMesh1 = 0;
AEVec2* char_prev_pos;
int Flag;

void Level1_Load()
{
	//../Code/Levels/Exported.txt
	if (ImportMapDataFromTxt("../Levels/leveldesign.txt"))
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
	



	std::cout << "    ";
	for (int x{ 0 }; x < 60; ++x)
	{
		if (x > 9)
			std::cout << x << " ";
		else
			std::cout << x << "  ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	for (int y{ 0 }; y < 25; ++y)
	{ 
		if (y > 9)
			std::cout << y << " | ";
		else
			std::cout << " " << y << " | ";
		
		for (int x{ 0 }; x < 60; ++x)
			std::cout << GetCellValue(x, y) << "  ";
		std::cout << std::endl;
	}
}

void Level1_Update()
{
	// Handling Input
	AEInputUpdate();
	Input_g_mode();

	Flag = CheckInstanceBinaryMapCollision(character->pos, character->scale);

	if (Flag == COLLISION_RIGHT)
	{
		SnapToCell(&character->pos.x);
		character->velocity.x = 0;
		Flag -= COLLISION_RIGHT;
		printf("RIGHT POS: %f, %f\n", character->pos.x, character->pos.y);
	}

	if (Flag == COLLISION_LEFT)
	{
		SnapToCell(&character->pos.x);
		character->velocity.x = 0;
		Flag -= COLLISION_LEFT;
		printf("LEFT POS: %f, %f\n", character->pos.x, character->pos.y);
	}

	if (Flag == COLLISION_TOP)
	{
		SnapToCell(&character->pos.y);
		character->velocity.y = 0;
		Flag -= COLLISION_TOP;
		// printf("POS: %d, %d\n", character->pos.x, character->pos.y);
	}

	if (Flag == COLLISION_BOTTOM)
	{
		SnapToCell(&character->pos.y);
		character->velocity.y = 0;
		Flag -= COLLISION_BOTTOM;
		// printf("POS: %d, %d\n", character->pos.x, character->pos.y);
	}

	//Updating the physics of the game e.g acceleration, velocity, gravity
	physics_update();

	camera_update(character->pos, character->velocity, character->scale);
	//For Debuging Camera
	//draw_static_obj();
}

void Level1_Draw()
{
	update_render_walls();
	update_render_hook();
	update_render_enemy();
	update_render_character();

	//For Debuging Camera
	// draw_cam_bounding_box(character->pos, character->pos);

	// debugging hotspot
	draw_cam_bounding_box({ character->pos.x + character->scale / 4, character->pos.y - character->scale / 2 },
		{ character->pos.x - character->scale / 4, character->pos.y + character->scale / 2 });

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