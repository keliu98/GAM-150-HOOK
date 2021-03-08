#include "ObjectManager.h"

Character* character;
Hook* hook;
Button* button_1;
std::vector<Wall> walls;

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

Character* create_character()
{
	Character* character = new Character{
		{0,0},		// Index spawn_index;
		{0,0},		// AABB  aabb;

		32.0f,		// float scale;

		{0,0},		//AEVec2 transform;
		{0,0},		// AEVec2 pos;
		{0,0},		// AEVec2 accel;
		{0,0},		// AEVec2 velocity;

		1.0f,		// float jump_height;
		1.0f,		// float gravity;

		1,			// int char_state;

		3,			// int lives;
		0,			// int damage;
	};
	return character;
}


Button* create_button()
{
	Button* button = new Button{
		40.0f,			//scale
		{0,0},		//AEVec2 transform;
		{0,0},		// AEVec2 pos;

	};
	return button;
}


std::vector<Enemy> create_enemy(std::vector<Enemy>& enemies)
{
	// create single enemy
	Enemy* enemy = new Enemy;

	// init values here

	enemies.push_back(*enemy);

	// load enemy graphic here? (Use render system)

	// return vector
	return enemies;
}

// When enemy is defeated by players
void destory_enemy(std::vector<Enemy>& enemies, int index)
{
	for (int i{ 0 }; i < enemies.size(); ++i)
	{
		if (i == index)
		{
			// remove that particular enemy
			delete& enemies[i];
			enemies.erase(enemies.begin());
			return;
		}
	}
}

void free_object(Character* character, Hook* hook, std::vector<Wall> walls)
{
	for (int i{0}; i < walls.size(); ++i)
	{
		// remove first element
		//delete & walls[i];
		walls.erase(walls.begin());
	}
	
	delete hook;
	delete character;
}


// Question: Use vector or array? Cause wall can be nullpointer.
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

