
/*!*************************************************************************
****
\file physics.cpp
\authors: Tan Wei Wen

\par DP email:  t.weiwen@digipen.edu

\par Course: CSD 1450
\par Project: Software Engineering Project 2
\date 160221


\brief //TODO

****************************************************************************
***/

#include "pch.h"

static float GRAVITY = 500.0f;
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

		//hook friction, lesser than normal friction
		//character->velocity.x = character->velocity.x * 0.995f;
	}
	else
	{
		//Horizontal Friction. 
		character->velocity.x = character->velocity.x * 0.97f;

	}


	//Gravity.
	AEVec2 gravity_dir{ 0.0f, -1.0f };
	set_accel_to_vel(character->velocity, gravity_dir, GRAVITY);


	//!!!!!!!!!!!!!!!! Temporary wall collision NEED TO CHANGE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (character->pos.y < 0.0f)
	{
		character->pos.y = 0.1f;
		character->velocity.y = 0;
	}

//------------------Updating Character physics---------------------
}

//Calculates and sets the velocity of the object using an flat acceleration value and a normalised direction vector. 
//The new velocity is assigned to the referenced velocity.
void set_accel_to_vel(AEVec2& vel, AEVec2 dir, float &accel)
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



