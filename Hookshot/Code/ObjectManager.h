#pragma once
#include "pch.h"

//Extern Pointers to use for objects
struct Character;
extern Character* character;

struct Hook;
extern Hook* hook;

struct Button;
extern Button* button_1;

//min is the bottom-left of the object
//max is the top-right of the object

struct AABB {
	AEVec2 min;
	AEVec2 max;
};

//Used for spliting the screen into multiple parts
struct Index {
	int x_index;
	int y_index;
};

enum char_state {
	moving_left,
	moving_right,
	jumping,
	falling,
	idle,
	onhook
};

struct Hook {
	bool flag;

	int hook_state;

	AEMtx33 transform;

	AEVec2 head_pos;
	AEVec2 center_pos;
	AEVec2 tail_pos;

	float curr_len;
	float max_len;

	AEVec2 pivot_pos;
	float arc_tan;
	float pivot_angle;
};

enum hook_state
{
	not_firing,
	firing,
	tethered
};

struct Character {
	Index spawn_index;
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
	//AABB  aabb;
	float scale;
	AEMtx33 transform;
	AEVec2 pos;
};

struct Wall {
	float scale;
	int type;

	Index spawn_index;
	AEVec2 position;
	AABB aabb;
}typedef Wall;

extern std::vector<Wall> walls;

//TODO for yong hui
enum wall_type
{

};

/*struct Button {
	float height;
	float width;

	AEVec2 position;
};*/


struct Render {
	// all the render stuff - add more
	char* texture;
	float scale;

};

//TO be done by yong hui
struct Enemy {
	//TODO
} typedef Enemy;

// --------------------------FUNCTIONS FROM OBJECTMANAGER.CPP---------------------------------------------
// Create hook
Hook* create_hook();

// Create character
Character* create_character();

// Create Buttons
Button* create_button();

// Create 1 singular enemy
std::vector<Enemy> create_enemy(std::vector<Enemy>&);

void create_wall(AEGfxVertexList* mesh, AEGfxTexture* texture, int type, float scale, AEVec2 pos);
// loadLevel is defined in LoadMap.cpp
extern void loadLevel(AEGfxVertexList* mesh, AEGfxTexture* texture, float scale, AEVec2 pos);

// When enemy is defeated by players (pass in enemy vec and index to delete)
void destory_enemy(std::vector<Enemy>&, int index); 

// Free all object
void free_object(Character* character, Hook* hook, std::vector<Wall> walls);
// -------------------------------------------------------------------------------------------------------

