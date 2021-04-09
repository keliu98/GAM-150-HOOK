/*!*************************************************************************
****
\file enemy.h
\authors: Lau Yong Hui

\par DP email:  l.yonghui@digipen.edu
			
\par Course: CSD 1450
\par Project: Software Engineering Project 2
\date 160221


\brief
  
 This source file contains the implementation for all the enemy related
  functions.

****************************************************************************/

#include "pch.h"
#include "collision.h"

AEVec2 dirL = { -1.0f, 0.0f };//set direction to move leftward
AEVec2 dirR = { 1.0f, 0.0f };//set direction to move rightward
AEVec2 idle = { 0.0f, 0.0f };// set idle state

void enemy_move_L(size_t i)
{
	set_accel_to_vel(enemies[i].velocity, dirL, 300.0f);//when enemy called to move left make enemy move towards the left side of the screen
}

void enemy_move_R(size_t i)
{
	set_accel_to_vel(enemies[i].velocity, dirR, 300.0f);//when enemy called to move right make enemy move towards the rightside side of the screen
}

void enemy_idle(size_t i) {

	set_accel_to_vel(enemies[i].velocity, idle, 0.0f);//make it so that the enemy is not moving
}
void enemy_jump(size_t i) {
	if (enemies[i].jump_state != jumping)//as long as enemy is not jumping
	{
		enemies[i].velocity.y += CHAR_HEIGHT_VEL;// enemy jump upward
		enemies[i].jump_state = jumping;//set state to jump
	}
}

void skitter_AI(size_t i) {

	//enemies[i].cliff_check.x = enemies[i].pos.x - 1.0f;
	//enemies[i].cliff_check.x = enemies[i].pos.y - 1.0f;

	//For checking if the character needs to change direction. If cell value returns 1 means there a floor.
	AEVec2 bottom_left = { enemies[i].pos.x - GRID_SCALE, enemies[i].pos.y - GRID_SCALE / 2 };
	AEVec2 bottom_right = { enemies[i].pos.x + GRID_SCALE, enemies[i].pos.y - GRID_SCALE / 2 };

	int left_hotspot = GetCellValue((int)bottom_left.x / GRID_SCALE, (int)(bottom_left.y / GRID_SCALE));//check left hotspot
	int right_hotspot = GetCellValue((int)bottom_right.x / GRID_SCALE, (int)(bottom_right.y / GRID_SCALE));//check right hotspot

	if (character->counter == 0 && (CollisionIntersection_RectRect(character->aabb, character->velocity, enemies[i].aabb, enemies[i].velocity))) {//check for collision with player
		--character->health;// reduce character health
		//ammoD = 3;
		release_hook();//releas the hook
		calculate_knockback(character->pos, enemies[i].pos, character->velocity, character->knockback);//induce knockback
		character->counter = 180;// set Iframe for player character to last for 180 frame (3 second)

	}
	if (character->counter > 0) {
		--character->counter;//as long as counter is more than 0 reduce it
	}

	if (character->health == 0) {//if it is zero
		//character->health = 3;
		next = GS_RESTART;// restart the game
	}

	if (enemies[i].d_switch == 0)
		enemy_move_L(i);//if direction switch is 0 move left

	if (enemies[i].d_switch == 1)//if one move right
		enemy_move_R(i);

	if (enemies[i].d_switch == 0 && ((enemies[i].grid_collision_flag & COLLISION_LEFT) == COLLISION_LEFT)//when moving left check for left collision
		|| enemies[i].d_switch == 0 && (left_hotspot == 0 && right_hotspot == 1))// or if left or right hotspot is detected
	{
		enemies[i].velocity.x *= -1;
		enemies[i].d_switch = 1;// change direction
	}
	else if (enemies[i].d_switch == 1 && ((enemies[i].grid_collision_flag & COLLISION_RIGHT) == COLLISION_RIGHT)//when moving right check for right collision
		|| enemies[i].d_switch == 1 && (right_hotspot == 0 && left_hotspot == 1)) //or if left or right hotspot is detected
	{
		enemies[i].velocity.x *= -1;
		enemies[i].d_switch = 0;// change direction
	}

	if (enemies[i].health <= 0)
	{
		enemies.erase(enemies.begin() + i);//if enemies  health reached zero, erase that particular enemy 
	}


}

void update_spikes()
{
	for (Spike& spike : spikes)
	{
		if (character->counter == 0 && (CollisionIntersection_RectRect(character->aabb, character->velocity, spike.aabb, {0,0}))) {////if player counter is 0(valnurable) and there is collision with spike
			--character->health;//reduce health
			release_hook();//release hook
			//ammoD = 3;
			calculate_knockback(character->pos, spike.position, character->velocity, character->knockback);//induce knock back
			character->counter = 180;//player counter set to 180
		}
	}
}

void update_hook_attack()
{
	for (Enemy& enemy : enemies)
	{
		if (CollisionIntersection_PointRect(hook->head_pos, enemy.aabb))//if hook collide with enemies
		{
			
			if (enemy.Iframe == 0)//and enemy is valnurable
				enemy.health -= 1;//reduce enemy health
		
			calculate_knockback(hook->head_pos, character->pos, enemy.velocity, enemy.knockback);//calculate the knockback

			hook->max_len = hook->curr_len;//stop the hook
			hook->pivot_pos = hook->head_pos;//set the piviot point on the tip of the hook
			enemy.Iframe = 1; //turn on enemy Iframe

		}

		if (!(CollisionIntersection_PointRect(hook->head_pos, enemy.aabb)))
		{
			enemy.Iframe = 0;// if the hook stop colliding with enemy turn off I frame
		}
	}
}

