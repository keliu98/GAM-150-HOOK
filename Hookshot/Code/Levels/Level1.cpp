/*!*************************************************************************
****
\file Level1.cpp
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


\brief
  This source file contains the implementation for all the level 1 
  functions.
****************************************************************************
***/

#include "../pch.h"
static bool check;

void Level1_Load()
{
	
	//Load Map Data from txt file
	if (!ImportMapDataFromTxt("../Levels/Level_1.txt"))
		next = GS_QUIT;

	//Load Music
	music_Load("../Music/LOST CIVILIZATION - NewAge MSCNEW2_41.wav");

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

	// load door/goal
	load_door_texture();

	// load buttons texture
	load_button_texture();

	// load spikes
	load_spike_texture();


	//---------------------Load Character Animation Textures----------------------------------------
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
}

void Level1_Initialize()
{
	//Ensure game is unpaused when reset
	PAUSE = false;

	//Translate the map data into the gameworld by creating objects
	IntializeLevel();

	//Intialize camera
	camera_init(character->pos);

	//Intialise physic
	physics_intialize();

	//Initalise Music
	music_Initialize();
}

void Level1_Update()
{
	// Handling Input
	AEInputUpdate();
	Input_g_mode();

	//If pause do not need update to run this few system
	if (PAUSE == false)
	{
		//Update Enemy AI e.g movement
		for (size_t i = 0; i < enemies.size(); i++)
		{
			create_AABB(enemies[i].aabb, enemies[i].pos, enemies[i].scale, enemies[i].scale);
			skitter_AI(i);

		}

		//Update Spikes Collision
		update_spikes();

		//Updating the physics of the game e.g acceleration, velocity, gravity
		physics_update();

		// Updating the Collision
		UpdateCollision();

		//Update Camera to stay within player
		camera_update(character->pos, character->velocity, character->scale);
		
		//Checks for win/lose condition
		CheckWinLose();
	}

	//Updates the pause menu
	UpdatePauseMenu();

	//Updates the button interaction
	UpdateButton();
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
	update_render_spikes();
	update_render_character();
	update_render_buttons();

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
	UnloadMapData();
	unload_render();
}