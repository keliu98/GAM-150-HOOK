#include "pch.h"
#include "collision.h"

AEVec2 dirL = { -1.0f, 0.0f };
AEVec2 dirR = { 1.0f, 0.0f };
AEVec2 idle = { 0.0f, 0.0f };

void enemy_move_L(size_t i)
{
	set_accel_to_vel(enemies[i].velocity, dirL, 300.0f);
}

void enemy_move_R(size_t i)
{
	set_accel_to_vel(enemies[i].velocity, dirR, 300.0f);
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

	enemies[i].cliff_check.x = enemies[i].pos.x - 1.0f;
	enemies[i].cliff_check.x = enemies[i].pos.y - 1.0f;

	//For checking if the character needs to change direction. If cell value returns 1 means there a floor.
	AEVec2 bottom_left = { enemies[i].pos.x - GRID_SCALE, enemies[i].pos.y - GRID_SCALE / 2 };
	AEVec2 bottom_right = { enemies[i].pos.x + GRID_SCALE, enemies[i].pos.y - GRID_SCALE / 2 };

	int left_hotspot = GetCellValue((int)bottom_left.x / GRID_SCALE, (int)(bottom_left.y / GRID_SCALE));
	int right_hotspot = GetCellValue((int)bottom_right.x / GRID_SCALE, (int)(bottom_right.y / GRID_SCALE));

	if (character->counter == 0 && (CollisionIntersection_RectRect(character->aabb, character->velocity, enemies[i].aabb, enemies[i].velocity))) {
		--character->health;
		ammoD = 3;
		release_hook();
		calculate_knockback(character->pos, enemies[i].pos, character->velocity, character->knockback);
		character->counter = 180;

	}
	if (character->counter > 0) {
		--character->counter;
	}

	if (character->health == 0) {
		//character->health = 3;
		next = GS_RESTART;
	}

	if (enemies[i].d_switch == 0)
		enemy_move_L(i);

	if (enemies[i].d_switch == 1)
		enemy_move_R(i);

	if (enemies[i].d_switch == 0 && ((enemies[i].grid_collision_flag & COLLISION_LEFT) == COLLISION_LEFT)
		|| enemies[i].d_switch == 0 && (left_hotspot == 0 && right_hotspot == 1))
	{
		enemies[i].velocity.x *= -1;
		enemies[i].d_switch = 1;
	}
	else if (enemies[i].d_switch == 1 && ((enemies[i].grid_collision_flag & COLLISION_RIGHT) == COLLISION_RIGHT)
		|| enemies[i].d_switch == 1 && (right_hotspot == 0 && left_hotspot == 1))
	{
		enemies[i].velocity.x *= -1;
		enemies[i].d_switch = 0;
	}

	if (enemies[i].health <= 0)
	{
		enemies.erase(enemies.begin() + i);
		score += 100;
	}


}

void update_spikes()
{
	for (Spike& spike : spikes)
	{
		if (character->counter == 0 && (CollisionIntersection_RectRect(character->aabb, character->velocity, spike.aabb, {0,0}))) {
			--character->health;
			release_hook();
			ammoD = 3;
			calculate_knockback(character->pos, spike.position, character->velocity, character->knockback);
			character->counter = 180;
		}
	}
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

