#include "../pch.h"

//Declaration of Variables.
AEGfxVertexList* pMesh1 = 0;

Character character;
float CHARACTER_ACCEL_HORI = 500.0f;
float GRAVITY = 500.0f;
float CHAR_HEIGHT = 50.0f;
float CHAR_HEIGHT_VEL;

void Level1_Load()
{
	// Will need to create a seperate file for the meshes.
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// 1 triangle at a time
	// X, Y, Color, texU, texV
	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 0.0f,
		0.5f, 0.0f, 0xFFFF0000, 0.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFF0000, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh1

	pMesh1 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh1, "Failed to create mesh 1!!");

}

void Level1_Initialize()
{
	character.scale = 32.0f;
	character.pos = {0.0f,0.0f};
	character.accel = {0.0f,0.0f};
	character.velocity = { 0.0f,0.0f };

	//TODO
	//Index spawn_index;
	//AABB  aabb;


	//float jump_height;
	//float gravity;

	//int char_state;

	//int lives;
	//int damage;

	//Hook* hook;

	CHAR_HEIGHT_VEL = create_vel_height(CHAR_HEIGHT, GRAVITY);
}

void Level1_Update()
{
	float delta_time = g_dt;

	// Handling Input
	AEInputUpdate();

	//Temporary for doing physics.cpp
	if (AEInputCheckCurr(AEVK_LEFT))
	{
		AEVec2 dir = {-1.0f, 0.0f};
		set_accel_to_vel(character.velocity, dir, CHARACTER_ACCEL_HORI);
	}

	if (AEInputCheckCurr(AEVK_RIGHT))
	{
		AEVec2 dir = {1.0f, 0.0f};
		set_accel_to_vel(character.velocity, dir, CHARACTER_ACCEL_HORI);
	}

	if (AEInputCheckTriggered(AEVK_UP) || AEInputCheckTriggered (AEVK_SPACE))
	{
		character.velocity.y += CHAR_HEIGHT_VEL;
	}

	//Within the loop, done constantly
	set_vel_to_pos(character.pos, character.velocity);

	//Horizontal Friction. 
	character.velocity.x = character.velocity.x * 0.97f;

	//Gravity.
	AEVec2 gravity_dir{ 0.0f, -1.0f };
	set_accel_to_vel(character.velocity, gravity_dir, GRAVITY);

	//Temporary wall collision
	if (character.pos.y < 0)
	{
		character.pos.y = 0.01;
		character.velocity.y = 0;
	}
	
}

void Level1_Draw()
{
	AEMtx33	trans, scale;

	// Compute the scaling matrix
	AEMtx33Scale(&scale, character.scale, character.scale);

	// Compute the translation matrix
	AEMtx33Trans(&trans, character.pos.x, character.pos.y);

	AEMtx33Concat(&character.transform, &trans, &scale);


	// Will need to create a seperate function for drawing all the objects.
	// Drawing object 1
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	// Set position for object 1
	AEGfxSetPosition(0.0f, 0.0f);
	// No texture for object 1
	AEGfxTextureSet(NULL, 0, 0);
	// Transforing the picture based on its matrix
	AEGfxSetTransform(character.transform.m);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);

	//Temporary for exiting the system
	if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
		next = GS_QUIT;
}

// Called if change state, for everything including reset
void Level1_Free()
{
	
}

//  Called if change state and State is NOT reset. ie Change levels. Do not unload if reseting.
void Level1_Unload()
{
	AEGfxMeshFree(pMesh1);
}