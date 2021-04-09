/*!*************************************************************************
****
\file ObjectManager.cpp
\par Project: Hookshot
\authors: Tan Wei Wen (40%)
		  Egi Tan (40%)
		  Yong Hui (20%)

\par DP email:  t.weiwen@digipen.edu
				egi.tan@digipen.edu
				l.yonghui@digipen.edu

\par Course: CSD 1450
\date 050421

\brief
This file contains the implementation for the objectmanager. It is responsible for
creating the objects and freeing them. It also has all the neccessary containers
for each of the object.

\par Copyright: All content � 2021 Digipen Institute of Technology Singapore. All
				rights reserved.

****************************************************************************
***/

#include "ObjectManager.h"

int lives = 3; //initialise live and set the starting amount to 3
int ammo =3; // set internal ammo to 3
int ammoD = 3;//set display ammo to 3

//Pointers for single object.
Character* character;
Hook* hook;
Button* button;//create button
std::vector<Button> buttons;//create a vector of buttons
std::vector<Wall> walls;
std::vector<Enemy> enemies;//create a vector of enemies
std::vector<Spike> spikes;

//Creating the hook object, used together with load map.
Hook* create_hook() {
	Hook* hook = new Hook{
		{false},      //bool flag

		{not_firing}, //int hook_state

		{0,0},		  //AEVec2 transform

		{4.0},		  //float scale;
		
		{0,0},        //AEVec2 head_pos
		{0,0},        //AEVec2 center_pos
		{0,0},        //AEVec2 tail_pos

		{0},          //float curr_len
		{0},          //float max_len

		{0,0},        //AEVec2 pivot_pos
		{0},          //float arc_tan
		{0},		  //float pivot_angle;
	};

	return hook;
}

//Creating the character object, used together with load map.
Character* create_character(AEVec2 pos)
{
	Character* character = new Character{
		{0,0},		// AABB  aabb;

		40.0f,		// float scale;

		{0,0},		//AEVec2 transform;
		pos,		// AEVec2 pos;
		{0,0},		// AEVec2 accel;
		{0,0},		// AEVec2 velocity;

		1.0f,		// float jump_height;
		1.0f,		// float gravity;

		1,			// int char_state;

		3,			// int health;
		0,			// int damage;
		0,			//Iframe (0: vulnerable, 1: invincible)
		0,			//damage counter
	};

	character->knockback.y = create_vel_height(10.0f, GRAVITY);
	character->knockback.x = 150.0f;

	return character;
}

//Create interactable buttons in game. 
void create_button(int state, const char* string, AEVec2 pos, float scale_x, float scale_y)
{
	Button button;
	
	// init values 
	button.state = state;// set button to defualt state
	button.scale.x = scale_x;//set x for scale
	button.scale.y = scale_y;// set y for scalw
	button.pos_ratio = pos;//set position ratio
	button.string = string;//set the string of the button
	button.highlight = false;// set default to bee non highlighted at the start
	buttons.push_back(button);//push back button by one at the beginning
}

//Creates the end point/goal of the game
AEVec2* create_ending_point(AEVec2 pos)
{
	AEVec2* end_position = new AEVec2{ pos };
	return end_position;
}

//Create a single enemy, used together with load map. Stored in a vector container
void create_enemy(int enemy_type, AEVec2 pos)
{
	// create single enemy
	Enemy enemy;
	
	//TODO intialise values
	enemy.scale = 40.0f;// set scale size to 40
	enemy.dir = 0.0f;// set direction to 0
	enemy.pos = pos;// set postion to the pass-in position 
	enemy.type = enemy_type;//set the type to the pass in type

	enemy.knockback.y = create_vel_height(30.0f, GRAVITY);//set verticle knockback
	enemy.knockback.x = 200.0f;//set horizontal knockback 

	enemy.velocity.x = 0;// set defualt horizontal velocity to 0
	enemy.velocity.y = 0;//set verticle velocity to 0
	enemy.jump_state = not_jumping;// set default jump state to not jumping
	enemy.d_switch = 0; //set directional switch to 0
	enemy.health = 3; // set health to 3
	enemy.Iframe = 0; // 1 = invincible, 0=vulnerable
	enemy.cliff_check = pos;//set cliff checker to 0
	enemies.push_back(enemy);//puch back the enemies vector
	
	//std::cout << "enemy created\n";
}

// When enemy is defeated by players, to remove the enemy from the vector container.
void destory_enemy(std::vector<Enemy>& enemies, int index)
{
	for (int i{ 0 }; i < enemies.size(); ++i)//scan through the enemy list
	{
		if (i == index) //if the enemy index is the same as the passed in index
		{
			// remove that particular enemy
			delete& enemies[i];
			enemies.erase(enemies.begin());//remove that enemy from the list
			return;
		}
	}
}

// Removes all objects in the game.
void free_objects()
{
	walls.clear();
	enemies.clear();
	spikes.clear();
	
	delete hook;
	delete character;
	delete end_position;
}

// Removes the buttons in the game
void free_button()
{
	buttons.clear();
}

// Creates a wall, used together with load map. Stored in a vector container.
void create_wall(int type, float scale, AEVec2 pos)
{
	// create a wall
	// Wall *wall = new Wall;
	Wall wall;

	// init values
	wall.type = type;
	wall.scale = scale;
	wall.position = pos;
	walls.push_back(wall);
}

// Creates a spike, used together with load map. Stored in a vector container.
void create_spikes(float scale, AEVec2 pos)
{
	// create a wall
	// Wall *wall = new Wall;
	Spike spike;

	spike.scale = scale;
	spike.position = pos;
	create_AABB(spike.aabb, spike.position, spike.scale, spike.scale);
	spikes.push_back(spike);
}

