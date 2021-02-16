#include "../pch.h"

//Declaration of Variables.
AEGfxVertexList* pMesh1 = 0;

float CHARACTER_ACCEL_HORI = 40.0f;
Character character;

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
}

void Level1_Update()
{
	float delta_time = g_dt;

	// Handling Input
	AEInputUpdate();

	//Temporary for doing physics.cpp
	if (AEInputCheckCurr(AEVK_LEFT))
	{
		character.accel = {-1.0f, 0.0f};

		//Scale the acceleration
		AEVec2Scale(&character.accel, &character.accel, CHARACTER_ACCEL_HORI);

		//Find the velocity according to the acceleration
		//newVel = Accleration * dt + currentVel 
		AEVec2Scale(&character.accel, &character.accel, delta_time);
		AEVec2Add(&character.velocity, &character.accel, &character.velocity);
	}

	if (AEInputCheckCurr(AEVK_RIGHT))
	{
		character.accel = {1.0f, 0.0f};

		//Scale the acceleration
		AEVec2Scale(&character.accel, &character.accel, CHARACTER_ACCEL_HORI);

		//Find the velocity according to the acceleration
		//newVel = Accleration * dt + currentVel 
		AEVec2Scale(&character.accel, &character.accel, delta_time);
		AEVec2Add(&character.velocity, &character.accel, &character.velocity);
	}

	//Within the loop, done constantly
	AEVec2 delta_velocity;
	AEVec2Scale(&delta_velocity, &character.velocity, delta_time);
	AEVec2Add(&character.pos, &delta_velocity, &character.pos);

	//Friction. 
	AEVec2Scale(&character.velocity, &character.velocity, 0.99f);
	
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