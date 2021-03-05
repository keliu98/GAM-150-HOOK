#include "../pch.h"

//Declaration of Variables.
AEGfxVertexList* pMesh1 = 0;


void Level1_Load()
{
	//../Code/Levels/Exported.txt
	if (ImportMapDataFromTxt("../Code/Levels/Map_1.txt"))
	{	
		PrintRetrievedInformation();
	}

	// Will need to create a seperate file for the meshes.
	// Informing the library that we're about to start adding triangles
	AEGfxMeshStart();

	// 2 triangle at a time
	// X, Y, Color, texU, texV

	AEGfxTriAdd(
		-0.5f, 0.5f, 0x808080, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 0.0f,
		0.5f, 0.5f, 0x808080, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0x808080, 0.0f, 0.0f,
		-0.5f, -0.5f, 0x808080, 0.0f, 0.0f,
		0.5f, 0.5f, 0x808080, 0.0f, 0.0f);

	// Saving the mesh (list of triangles) in pMesh1

	pMesh1 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh1, "Failed to create mesh 1!!");
}

void Level1_Initialize()
{
	character = create_character();
	hook = create_hook();


	physics_intialize();
	camera_init(character->pos);
}

void Level1_Update()
{
	float delta_time = g_dt;


	//-------------------------START OF INPUT------------------------------

	// Handling Input
	AEInputUpdate();
	/*
	//Temporary for doing physics.cpp
	if (AEInputCheckCurr(AEVK_A))

	{
		AEVec2 dir = {-1.0f, 0.0f};
		set_accel_to_vel(character->velocity, dir, CHARACTER_ACCEL_HORI);
	}

	if (AEInputCheckCurr(AEVK_D))
	{
		AEVec2 dir = {1.0f, 0.0f};
		set_accel_to_vel(character->velocity, dir, CHARACTER_ACCEL_HORI);
	}

	if (AEInputCheckTriggered(AEVK_W) && hook->flag == false)
	{
		character->velocity.y += CHAR_HEIGHT_VEL;
	}*/

	Input_g_mode();



	//-------------------------END OF INPUT------------------------------
	
	physics_update();

	camera_update(character->pos, character->velocity, character->scale);
		//For Debuging Camera
		draw_cam_bounding_box();
		draw_static_obj();
}

void Level1_Draw()
{
	AEMtx33	trans, scale, rot;


	//---------for drawing the character--------------
	// Compute the scaling matrix
	AEMtx33Scale(&scale, character->scale, character->scale);

	// Compute the translation matrix
	AEMtx33Trans(&trans, character->pos.x, character->pos.y);

	AEMtx33Concat(&character->transform, &trans, &scale);

	// Will need to create a seperate function for drawing all the objects.
	// Drawing object 1
	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	// No texture for object 1
	AEGfxTextureSet(NULL, 0, 0);
	// Transforing the picture based on its matrix
	AEGfxSetTransform(character->transform.m);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);


	//---------for drawing the hook------------

	if (hook->flag == true)
	{
		//Scale it by the length of the hook
		AEMtx33Scale(&scale, hook->curr_len, 4.0f);
		// Compute the translation matrix
		AEMtx33Trans(&trans, hook->center_pos.x, hook->center_pos.y);
		//Rotate it by the angle hooked
		AEMtx33Rot(&rot, hook->pivot_angle);

		AEMtx33Concat(&hook->transform, &rot, &scale);
		AEMtx33Concat(&hook->transform, &trans, &hook->transform);

		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		// No texture for object 1
		AEGfxTextureSet(NULL, 0, 0);
		// Transforing the picture based on its matrix
		AEGfxSetTransform(hook->transform.m);
		// Drawing the mesh (list of triangles)
		AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);
	}




	//Temporary for exiting the system
	if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
		next = GS_QUIT;
}

// Called if change state, for everything including reset
void Level1_Free()
{
	FreeMapData();
	free_object(character, hook);
	AEGfxMeshFree(pMesh1);
}

//  Called if change state and State is NOT reset. ie Change levels. Do not unload if reseting.
void Level1_Unload()
{
	
}