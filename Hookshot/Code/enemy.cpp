#include "pch.h"
#include "collision.h"

AEVec2 dirL = { -1.0f, 0.0f };
AEVec2 dirR = { 1.0f, 0.0f };
AEVec2 idle = { 0.0f, 0.0f };

void enemy_move_L(size_t i) {
	--enemies[i].cliff_check.x;
	--enemies[i].cliff_check.y;
	set_vel_to_pos(enemies[i].pos, enemies[i].velocity);
	set_accel_to_vel(enemies[i].velocity, dirL, 200.0f);
}

void enemy_move_R(size_t i) {
	--enemies[i].cliff_check.x;
	++enemies[i].cliff_check.y;
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
	
		enemies[i].cliff_check.x = enemies[i].pos.x-1.0f;
		enemies[i].cliff_check.x = enemies[i].pos.y-1.0f;
		std::cout << GetCellValue(int(enemies[i].cliff_check.x), int(enemies[i].cliff_check.y))<<"\n";
	if (character->counter == 0 && (CollisionIntersection_RectRect(character->aabb, character->velocity, enemies[i].aabb, enemies[i].velocity))) {
		--character->health;
		character->counter = 180;
		std::cout << character->health;
		//std::cout << "check";

	}
	if (character->counter > 0) {
		--character->counter;
		//std::cout << character->counter;
	}

	if (character->health == 0) {
		character->health = 3;
		next=GS_RESTART;
	}

	if (enemies[i].d_switch == 0)
		enemy_move_L(i);

	if (enemies[i].d_switch == 1)
		enemy_move_R(i);

	if ((enemies[i].grid_collision_flag == COLLISION_LEFT)
		|| !GetCellValue((int)enemies[i].cliff_check.x/40, (int) enemies[i].cliff_check.y/40))
	{
		
		enemies[i].d_switch = 1;
	}
	if ((enemies[i].grid_collision_flag == COLLISION_RIGHT)
		|| !GetCellValue(((int)enemies[i].cliff_check.x)/40, ((int)enemies[i].cliff_check.y)/40))
	{
		enemies[i].d_switch = 0;
	}

	if (enemies[i].health <= 0)
		enemies.erase(enemies.begin() + i);

}

