#include "ObjectManager.h"

Hook* create_hook() {
	Hook* hook = new Hook;

	// init values here


	return hook;
}

Character* create_character(Hook* hook)
{
	Character* character = new Character{
		{0,0},		// Index spawn_index;
		{0,0},		// AABB  aabb;
		1.0f,		// float scale;

		{0,0},		// AEVec2 pos;
		{0,0},		// AEVec2 accel;
		{0,0},		// AEVec2 velocity;

		1.0f,		// float jump_height;
		1.0f,		// float gravity;

		1,			// int char_state;

		3,			// int lives;
		0,			// int damage;

		hook		// Hook* hook;
	};
	return character;
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

void free_object(std::vector<Enemy>& enemies, Character* character, Hook* hook)
{
	for (int i{0}; i < enemies.size(); ++i)
	{
		// remove first element
		delete &enemies[i];
		enemies.erase(enemies.begin());
	}
	
	delete hook;
	delete character;
}


// Question: Use vector or array? Cause wall can be nullpointer.
//std::vector<Wall> create_wall (std::vector<Wall>& walls, int type, float scale, AEVec2 pos)
//{
//	// create a wall
//	Wall *wall = new Wall;
//
//	// init values
//	wall->type = type;
//	wall->scale = scale;
//	wall->position = pos;
//	walls.push_back(*wall);
//
//	// load wall graphic here?
//
//	// return vector
//	return walls;
//}

