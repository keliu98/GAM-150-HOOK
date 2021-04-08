#include "../pch.h"
static bool check;

void Level1_Load()
{
	std::cout << "LOADDDDDD" << std::endl;
	music_Load("../Music/EVERYBODYS DANCING - WorldMusic MSCLAT1_06.wav");


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

	//load bg
	load_bg_render();

	// loading wall texture
	load_dirt_render();

	// loading character texture
	load_character_render();

	// load enemy_texture
	load_enemy_texture();

	// load hook_texture
	load_hook_render();

	// load dppr
	load_door_texture();

	// load buttons texture
	load_button_texture();

	//---------------------ADDED IN FORM LIU KE MERGE----------------------------------------
	//load_character render actions run to the right
	load_character_render_right();

	// load character render actions run to the left
	load_character_render_left();

	// load character render actions jump facing right direction
	load_character_render_jumpleft();

	// load character render actions jump facing right direction
	load_character_render_jumpright();

	// load character render shoot hook to right
	load_character_render_shootleft();

	// load character rendeer shoot hook to left
	load_character_render_shootright();

	// load character swinging left on the hook
	load_character_render_swingleft();

	// load character swinging right on the hook
	load_character_render_swingright();

	//---------------------ADDED IN FORM LIU KE MERGE----------------------------------------

}

void Level1_Initialize()
{
	PAUSE = false;

	//Translate the map data into the gameworld by creating objects
	IntializeLevel();

	//Intialize camera
	camera_init(character->pos);

	//Intialise physic
	physics_intialize();

	music_Initialize();

	
}

void Level1_Update()
{
	// Handling Input
	AEInputUpdate();
	Input_g_mode();


	if (PAUSE == false)
	{
		//Updating the physics of the game e.g acceleration, velocity, gravity
		physics_update();

		// Updating the Collision
		UpdateCollision();

		camera_update(character->pos, character->velocity, character->scale);

		AEVec2 dir = { -1.0f, 0.0f };

		//enermy AI
		for (size_t i = 0;i < enemies.size(); i++)
		{
			create_AABB(enemies[i].aabb, enemies[i].pos, enemies[i].scale, enemies[i].scale);
			skitter_AI(i);

		}

		CheckWinLose();
	}

	//Updates the pause menu
	UpdatePauseMenu();

	//Updates the button interaction
	UpdateButton();

	//if (!sound_mute && !check)
	//{
	//	music_Initialize();
	//	check = true;
	//	std::cout << " RUN: " << std::endl;
	//}

}

void Level1_Draw()
{
	static char text[100];
	memset(text, 0, 100 * sizeof(char));

	update_render_bg();
	update_render_door();
	update_render_walls();
	update_render_hook();
	update_render_enemy();
	update_render_character();
	update_render_buttons();

	//For Debuging Camera
	/*draw_cam_bounding_box({ end_position->x - 40 * 4, end_position->y - 40 * 4 }, *end_position );*/

	// print lives
	sprintf_s(text, "Health: %d", character->health);
	PrintText(text, NORMAL, { -0.9f, -0.85f });
	sprintf_s(text, "Lives: %d", lives);
	PrintText(text, NORMAL, { -0.9f, -0.95f });
	sprintf_s(text, "Shots: %d/3", ammoD);
	PrintText(text, NORMAL, { 0.4f, -0.95f });
}

// Called if change state, for everything including reset
void Level1_Free()
{
	music_Free();
	free_objects();
	free_button();
}

//  Called if change state and State is NOT reset. ie Change levels. Do not unload if reseting.
void Level1_Unload()
{
	music_Unload();
	FreeMapData();
	unload_render();
}