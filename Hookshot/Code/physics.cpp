/*!*************************************************************************
****
\file physics.cpp
\par Project: Hookshot
\authors: Tan Wei Wen (100%)

\par DP email:  t.weiwen@digipen.edu

\par Course: CSD 1450
\date 050421

\brief
This file contains the implementation for the physics system of the game. It 
calcuate the positions of objects by simulating simplified real life physics.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. All
				rights reserved.

****************************************************************************
***/

#include "pch.h"

const float GRAVITY = 500.0f;
static float CHAR_HEIGHT = 50.0f;
float CHAR_HEIGHT_VEL;

void physics_intialize()
{
	CHAR_HEIGHT_VEL = create_vel_height(CHAR_HEIGHT, GRAVITY);
}

void physics_update()
{

//------------------Updating Character physics---------------------

	//Within the loop, done constantly
	set_vel_to_pos(character->pos, character->velocity);

	
	if (hook->hook_state == tethered)
	{
		//Update position based on arc on hook, if the player is outside the range, pull it back.
		hook_char_pos_update();


		//Hook friction, lesser than normal friction
		character->velocity.x = character->velocity.x * 0.995f;
	}
	else
	{
		//Normal Character Horizontal Friction. 
		character->velocity.x = character->velocity.x * 0.95f;

	}

	//Gravity only when jumping.
	AEVec2 gravity_dir{ 0.0f, -1.0f };
	if ((character->grid_collision_flag & COLLISION_BOTTOM) != COLLISION_BOTTOM)
		set_accel_to_vel(character->velocity, gravity_dir, GRAVITY);



//------------------Updating Enemy physics---------------------

	//TODO KNOCKBACK AND COLLISION AYYEE
	for (Enemy& enemy : enemies)
	{
		//Setting velocity to position
		set_vel_to_pos(enemy.pos, enemy.velocity);

		//Gravity.
		set_accel_to_vel(enemy.velocity, gravity_dir, GRAVITY);

		//Horizontal Friction. 
		enemy.velocity.x = enemy.velocity.x * 0.95f;
	}

}

//Calculates and sets the velocity of the object using an flat acceleration value and a normalised direction vector. 
//The new velocity is assigned to the referenced velocity.
void set_accel_to_vel(AEVec2& vel, AEVec2 dir, float const accel)
{
	AEVec2 accel_vector;

	//Scale the acceleration by the directional vector
	AEVec2Scale(&accel_vector, &dir, accel);

	//Find the velocity according to the acceleration
	//newVel = Accleration * dt + currentVel 
	AEVec2Scale(&accel_vector, &accel_vector, g_dt);
	AEVec2Add(&vel, &accel_vector, &vel);
}

//Calculates and sets the position of the object using an flat velocity value and a normalised direction vector. 
//The new velocity is assigned to the referenced velocity.
void set_vel_to_pos(AEVec2& pos, AEVec2 dir, float &vel)
{
	AEVec2 vel_vector;

	//Scale the acceleration by the directional vector
	AEVec2Scale(&vel_vector, &dir, vel);

	//Find the position according to the velocity
	//newPos = velocity * dt + currentpos 
	AEVec2Scale(&vel_vector, &vel_vector, g_dt);
	AEVec2Add(&pos, &vel_vector, &pos);
}

//Calculates and sets the position of the object using an velocity vector. Needs to be used in the game loop, occurs every frame.
void set_vel_to_pos(AEVec2& pos, AEVec2 &vel)
{
	AEVec2 delta_vel;
	AEVec2Scale(&delta_vel, &vel, g_dt);
	AEVec2Add(&pos, &delta_vel, &pos);
}

//Takes in the height and then outputs the required velocity. TO only be called once during intialise, not used within the game loop
float create_vel_height(float height, float gravity)
{
	// Square root 2g(h)
	return sqrt(2 * gravity * height);
}

//Calculates the knockback. The direction is based on two position and it changes depending the velocity of the object depending on the knockback strength.
void calculate_knockback(AEVec2& pos1, AEVec2& pos2, AEVec2& velocity, AEVec2 knockback)
{
	//Getting the direction of the knockback
	AEVec2 knockback_dir;
	AEVec2Sub(&knockback_dir, &pos1, &pos2);
	AEVec2Normalize(&knockback_dir, &knockback_dir);

	//Scaling the x-dir knockback by knockback.x
	AEVec2Scale(&knockback_dir, &knockback_dir, knockback.x);

	//Scaling the y-dir knockback by knockback.y for a jumping up effect.
	knockback_dir.y += knockback.y;
	velocity = knockback_dir;
}

