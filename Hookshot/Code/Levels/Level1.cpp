#include "../pch.h"

//Declaration of Variables.
AEGfxVertexList* pMesh1 = 0;

// For drawing of wall
AEGfxVertexList* wall_mesh;
AEGfxTexture* wall_texture;
AEVec2 wall_pos; // store bottom left of the position
float wall_size = 20.0f;

void Level1_Load()
{
	//../Code/Levels/Exported.txt
	if (ImportMapDataFromTxt("../Levels/leveldesign.txt"))
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

	wall_mesh = load_mesh(20.0f);
	wall_texture = load_texture("../Images/Dirt1.png");
}

void Level1_Initialize()
{
	character = create_character();
	hook = create_hook();

	physics_intialize();
	camera_init(character->pos);

	// init wall pos
	wall_pos = { AEGfxGetWinMinX() + wall_size, AEGfxGetWinMinY() + wall_size };
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
	// load the level by drawing walls
	loadLevel(wall_mesh, wall_texture, wall_size, wall_pos);

	AEMtx33	trans, scale, rot;

	// draw_render1({ 100,100 }, wall_mesh, wall_texture);

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
	AEGfxMeshFree(pMesh1);
	free_object(character, hook, walls);
	// free wall mesh
	free_render(wall_mesh, wall_texture);
}

//  Called if change state and State is NOT reset. ie Change levels. Do not unload if reseting.
void Level1_Unload()
{
	
}