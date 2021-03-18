#include "ObjectManager.h"
#include "collision.h"
Character* character;
Hook* hook;
Button* button;
Health* health;
std::vector<Button> buttons;
std::vector < Health > heart;
std::vector<Wall> walls;
std::vector<Enemy> enemies;

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

		32.0f,		// float scale;

		{0,0},		//AEVec2 transform;
		pos,		// AEVec2 pos;
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


void create_button(int type, AEVec2 pos, float scale)
{
	Button button;
	
	// init values
	button.type = type;
	button.scale = scale;
	button.pos = pos;
	create_AABB(button.aabb, button.pos, button.scale);
	buttons.push_back(button);
	
}

void create_health(int type, AEVec2 pos, float scale)
{
	Button button;

	// init values
	button.type = type;
	button.scale = scale;
	button.pos = pos;
	create_AABB(button.aabb, button.pos, button.scale);
	buttons.push_back(button);
}




void create_enemy(int enemy_type, AEVec2 pos)
{
	// create single enemy
	Enemy enemy;
	
	//TODO intialise values
	enemy.scale = 32.0f;
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

void free_button(std::vector<Button> buttons)
{
	for (int i{ 0 }; i < buttons.size(); ++i)
	{
		// remove first element
		//delete & walls[i];
		buttons.erase(buttons.begin());
	}

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

