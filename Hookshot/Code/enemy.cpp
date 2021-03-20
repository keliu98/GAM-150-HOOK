#include "pch.h"
#include "collision.h"

AEVec2 dirL = { -1.0f, 0.0f };
AEVec2 dirR = { 1.0f, 0.0f };
AEVec2 idle = { 0.0f, 0.0f };

void enemy_move_L(size_t i) {
	set_vel_to_pos(enemies[i].pos, enemies[i].velocity);
	set_accel_to_vel(enemies[i].velocity, dirL, 200.0f);
}

void enemy_move_R(size_t i) {
	set_vel_to_pos(enemies[i].pos, enemies[i].velocity);
	set_accel_to_vel(enemies[i].velocity, dirR, 200.0f);
}

void enemy_idle(size_t i) {

	set_accel_to_vel(enemies[i].velocity, idle, 0.0f);
}

void enemy_jump(size_t i) {
	if (enemies[i].jump_state != jumping)
	{
		character->velocity.y += CHAR_HEIGHT_VEL;
		character->char_state = jumping;
	}
}

void skitter_AI(size_t i) {

	if ( CollisionIntersection_RectRect(character->aabb, character->velocity, enemies[i].aabb, enemies[i].velocity))
	{
		//character->health -= 1;
		//character->counter = 60;
		std::cout << character->health;

	}

//	if (character->counter > 0) {
		//--character->counter;
	//	std::cout << character->counter;
	//}

	if (enemies[i].d_switch == 0)
		enemy_move_L(i);

	if (enemies[i].d_switch == 1)
		enemy_move_R(i);
	if ((enemies[i].grid_collision_flag) == COLLISION_LEFT) {
		enemies[i].d_switch = 1;
	}
	if ((enemies[i].grid_collision_flag) == COLLISION_RIGHT) {
		enemies[i].d_switch = 0;
	}

	if(enemies[i].health<=0)
	enemies.erase(enemies.begin()+i);



} 

