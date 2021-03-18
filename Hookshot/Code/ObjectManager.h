#pragma once
#include "pch.h"

//Extern Pointers to use for objects
struct Character;
extern Character* character;

struct Hook;
extern Hook* hook;

struct Button;
extern std::vector<Button> buttons;

//Extern list to use for walls and enemies
struct Wall;
extern std::vector<Wall> walls;

struct Enemy;
extern std::vector<Enemy> enemies;

//-----------------------------------------------------------

struct AABB {
	AEVec2 min; //min is the bottom-left of the object
	AEVec2 max; //max is the top-right of the object
};

enum char_state {
	moving_left,
	moving_right,
	jumping,
	falling,
	idle,
	onhook
};

enum hook_state
{
	not_firing,
	firing,
	tethered
};

enum button_type
{
	TEMP,
	TITLE,
	OPTION1
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

	int lives;
	int damage;

	Hook* hook;
};

struct Button {
	
	float scale; //image scale

	//width
	//height 

	int type;
	AEMtx33 transform;
	AEVec2 pos;
	AABB  aabb;
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
	AABB aabb;
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

	int lives;
	int damage;

	AEVec2 knockback;
};

// --------------------------FUNCTIONS FROM OBJECTMANAGER.CPP---------------------------------------------
// Create hook
Hook* create_hook();

// Create character
Character* create_character(AEVec2 pos);

// Create Buttons
void create_button(int button_type, AEVec2 pos, float scale);

// Inserts a enemy into the vecot list enemies
void create_enemy(int enemy_type, AEVec2 pos);

// Inserts a wall into the vector list walls
void create_wall(int type, float scale, AEVec2 pos);

// When enemy is defeated by players (pass in enemy vec and index to delete)
void destory_enemy(std::vector<Enemy>&, int index); 
 
//Free buttons
void free_button(std::vector<Button> buttons);

// Free all object
void free_object(Character* character, Hook* hook, std::vector<Wall> walls);
// -------------------------------------------------------------------------------------------------------

