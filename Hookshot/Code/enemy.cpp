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
		enemies[i].velocity.y += CHAR_HEIGHT_VEL;
		enemies[i].jump_state = jumping;
	}
}

void skitter_AI(size_t i) {
	
		enemies[i].cliff_check.x = enemies[i].pos.x-1.0f;
		enemies[i].cliff_check.x = enemies[i].pos.y-1.0f;

		AEVec2 bottom_left = { enemies[i].pos.x - GRID_SCALE / 4, enemies[i].pos.y - GRID_SCALE / 2 };
		AEVec2 bottom_right = { enemies[i].pos.x + GRID_SCALE / 4, enemies[i].pos.y - GRID_SCALE / 2 };

		//For checking if the character needs to change direction. If cell value returns 1 means there a floor.

		//heading left, bottom left is empty, need to change direction
		if (GetCellValue((int)bottom_left.x / GRID_SCALE, (int)(bottom_left.y / GRID_SCALE) + 1))
		{
			enemies[i].velocity.x = enemies[i].velocity.x * -1; 
		}

		//else if (GetCellValue((int)bottom_left.x / GRID_SCALE, (int)bottom_left.y / GRID_SCALE) &&
		//	!GetCellValue((int)bottom_right.x / GRID_SCALE, (int)bottom_right.y / GRID_SCALE))
		//{
		//	enemies[i].velocity.x = enemies[i].velocity.x * -1;
		//}
		



		//std::cout << GetCellValue(int(enemies[i].cliff_check.x), int(enemies[i].cliff_check.y))<<"\n";

	if (character->counter == 0 && (CollisionIntersection_RectRect(character->aabb, character->velocity, enemies[i].aabb, enemies[i].velocity))) {
		--character->health;
		//knockback here
		calculate_knockback(character->pos, enemies[i].pos, character->velocity, character->knockback);

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

void update_hook_attack()
{
	for (Enemy& enemy : enemies)																			
	{
		if (CollisionIntersection_PointRect(hook->head_pos, enemy.aabb))									
		{
			//new code here
			if (enemy.Iframe == 0)
				enemy.health -= 1;
			//new code here
			std::cout << "hook - enemy collison";
			calculate_knockback(hook->head_pos, character->pos, enemy.velocity, enemy.knockback);

			hook->max_len = hook->curr_len;
			hook->pivot_pos = hook->head_pos;
			enemy.Iframe = 1;

		}

		if (!(CollisionIntersection_PointRect(hook->head_pos, enemy.aabb)))
		{
			enemy.Iframe = 0;
		}
	}
}

