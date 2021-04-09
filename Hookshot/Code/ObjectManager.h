/*!*************************************************************************
****
\file ObjectManager.h
\par Project: Hookshot
\authors: Tan Wei Wen (35%)
		  Egi Tan (35%)
		  Yong Hui (30%)

\par DP email:  t.weiwen@digipen.edu
				egi.tan@digipen.edu
				l.yonghui@digipen.edu

\par Course: CSD 1450
\date 050421

\brief
This file contains the interface for the objectmanager. It is has the functions that
are responsible for creating the objects and freeing them. It also externs all the
neccessary containers for each of the object.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. All
				rights reserved.

****************************************************************************
***/

#pragma once
#include "pch.h"

//Extern Pointers to use for objects
struct Character;
extern Character* character;

struct Hook;
extern Hook* hook;

struct Button;
extern std::vector<Button> buttons;

extern AEVec2* end_position;

//Extern list to use for walls and enemies and spikes
struct Wall;
extern std::vector<Wall> walls;

struct Enemy;
extern std::vector<Enemy> enemies;

struct Spike;
extern std::vector<Spike> spikes;

// Extern global variables related to the objects.
extern int lives;
extern int ammo;
extern int ammoD;



//-------------- START OF STRUCTURE DECLARATIONS---------------------

struct AABB {
	AEVec2 min; //min is the bottom-left of the object
	AEVec2 max; //max is the top-right of the object
};

enum char_state {
	jumping,
	not_jumping,
};

enum hook_state
{
	not_firing,
	firing,
	tethered
};

enum wall_type
{
	TEMP_WALL,
	WALL1,
	WALL2,
	WALL3
};

enum enemy_type
{
	TEMP_ENEMY,
	BASIC,
	ELITE,
};

struct Hook {
	bool flag;

	int hook_state;

	AEMtx33 transform;

	float scale;

	AEVec2 head_pos;
	AEVec2 center_pos;
	AEVec2 tail_pos;

	float curr_len;
	float max_len;

	AEVec2 pivot_pos;
	float arc_tan;
	float pivot_angle;
	
};


struct Character {
	AABB  aabb;

	float scale;
	AEMtx33 transform;

	AEVec2 pos;
	AEVec2 accel;
	AEVec2 velocity;
	
	float jump_height;
	float gravity;

	int char_state;
	int health;
	int damage;

	Hook* hook;
	int Iframe;
	int counter;

	int grid_collision_flag;
	AEVec2 knockback;
};

struct Button {
	
	AEVec2 scale;
	int state;
	AEMtx33 transform;
	AEVec2 pos_ratio;
	AEVec2 pos_trans;
	AABB  aabb;
	bool  highlight;
	const char* string;
};

struct Health {
	size_t total;
	float scale;
	int type;
	AEMtx33 transform;
	AEVec2 pos;
};


struct Wall {

	float scale;
	int type;

	AEVec2 position;
};

struct Spike{
	float scale;
	AEVec2 position;

	AABB  aabb;
};


struct Enemy {
	AABB  aabb;

	float scale;
	float dir;
	AEMtx33 transform;

	AEVec2 pos;
	AEVec2 velocity;

	float jump_height;
	float gravity;

	int type;

	int health;

	AEVec2 knockback;
	int jump_state;
	int grid_collision_flag;
	int d_switch;
	int Iframe;
};

//-------------- END OF STRUCTURE DECLARATIONS---------------------

// --------------------------FUNCTIONS FROM OBJECTMANAGER.CPP---------------------------------------------

/**************************************************************************/
/*!
	To create the hook object, used together with load map.
*/
/**************************************************************************/

Hook* create_hook();

/**************************************************************************/
/*!
	To create the character object, used together with load map.
*/
/**************************************************************************/

Character* create_character(AEVec2 pos);

/**************************************************************************/
/*!
	To create an interactable button. Position is based on the 
	ratio of the screen. Following the way fonts are drawn.
*/
/**************************************************************************/

// Create Buttons
void create_button(int state, const char* string, AEVec2 pos, float scale_x, float scale_y);

/**************************************************************************/
/*!
	To create the enemy object, used together with load map. Stored 
	in a vector container
*/
/**************************************************************************/

// Inserts a enemy into the vecot list enemies
void create_enemy(int enemy_type, AEVec2 pos);

/**************************************************************************/
/*!
	To create the wall object, used together with load map. Stored
	in a vector container
*/
/**************************************************************************/

// Inserts a wall into the vector list walls
void create_wall(int type, float scale, AEVec2 pos);

/**************************************************************************/
/*!
	To create the spike object, used together with load map. Stored
	in a vector container
*/
/**************************************************************************/

//Inserts a spikes into the vector list walls.
void create_spikes(float scale, AEVec2 pos);

/**************************************************************************/
/*!
	To remove enemy from the vector container. Takes in an index to remove
	that specific enemy.
*/
/**************************************************************************/

void destory_enemy(std::vector<Enemy>&, int index); 

/**************************************************************************/
/*!
	Removes the buttons from the game
*/
/**************************************************************************/
 
void free_button();

/**************************************************************************/
/*!
	Creates the ending point in the game
*/
/**************************************************************************/

AEVec2* create_ending_point(AEVec2 pos);

/**************************************************************************/
/*!
	Removes all objects in the game.
*/
/**************************************************************************/

void free_objects();


