#include "ObjectManager.h"

int lives = 3;
Character* character;
Hook* hook;
Button* button_1;
std::vector<Wall> walls;
std::vector<Enemy> enemies;
AEVec2* end_position;

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
	};
	return character;
}


Button* create_button()
{
	Button* button = new Button{
		{0,0},
		40.0f,			//scale
		{0,0},		//AEVec2 transform;
		{0,0},		// AEVec2 pos;

	};
	return button;
}

AEVec2* create_ending_point(AEVec2 pos)
{
	AEVec2* end_position = new AEVec2{ pos };
	return end_position;
}

void create_enemy(int enemy_type, AEVec2 pos)
{
	// create single enemy
	Enemy enemy;
	
	//TODO intialise values
	enemy.scale = 40.0f;
	enemy.dir = 0.0f;
	enemy.pos = pos;
	enemy.type = enemy_type;

	enemy.knockback.y = create_vel_height(30.0f, GRAVITY);
	enemy.knockback.x = 200.0f;

	enemy.velocity.x = 0;
	enemy.velocity.y = 0;

	enemies.push_back(enemy);
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

void free_objects()
{
	walls.clear();
	walls.shrink_to_fit();

	std::cout << walls.size() << '\n';
	std::cout << walls.capacity() << '\n';

	for (int i{0}; i < walls.size(); ++i)
	{
		// remove first element
		//delete & walls[i];
		walls.erase(walls.begin());
		std::cout << i << '\n';
	}

	for (int i{ 0 }; i < enemies.size(); ++i)
	{
		// remove first element
		//delete & walls[i];
		enemies.erase(enemies.begin());
		
	}
	
	delete hook;
	delete character;
	delete end_position;
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

