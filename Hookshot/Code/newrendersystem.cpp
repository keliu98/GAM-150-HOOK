
#include "pch.h"

//globals for tracking texture
static const int MAX_TEXTURE = 20;
AEGfxTexture* texturelist[MAX_TEXTURE];
int texture_count;

//Pointer to square mesh
AEGfxVertexList* square_mesh;

//Pointer to the wall texture
AEGfxTexture* wall_texture;

//Pointer to the character texture
AEGfxTexture* character_texture;

//Pointer to the hook texture
AEGfxTexture* hook_texture;

//Pointer to the enemy texture
AEGfxTexture* enemy_texture;

//Pointer to the health texture
AEGfxTexture* health_texture;

struct Render
{
	AEVec2 pos;
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTexture;

	float dir;
	float x_scale;
	float y_scale;

	AEMtx33 transform;
};

void draw_render(Render& render);

void load_square_mesh()
{

	AEGfxMeshStart();

	AEGfxTriAdd(
		-0.5, -0.5, 0x00FF00FF, 0.0f, 1.0f,
		0.5, -0.5, 0x00FFFF00, 1.0f, 1.0f,
		-0.5, 0.5, 0x0000FFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5, -0.5, 0x00FFFFFF, 1.0f, 1.0f,
		0.5, 0.5, 0x00FFFFFF, 1.0f, 0.0f,
		-0.5, 0.5, 0x00FFFFFF, 0.0f, 0.0f);


	square_mesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(square_mesh, "Failed to create mesh 1!!");
}


AEGfxTexture* load_texture(const char* image)
{

	AEGfxTexture* pTex1st = AEGfxTextureLoad(image);
	AE_ASSERT_MESG(pTex1st, "Failed to create texture1!!");
	texturelist[texture_count] = pTex1st;
	texture_count++;

	return pTex1st;
}

//WEI_WEN: PLS LIU KE I AM LEAVING THIS TO YOU
//!!!!!!Need to change this to that it becomes specific ie load walls texture only when neccessary. cause right now its loading all textures!!!!
//for example we dont want to load wall texture for main menu 

void load_render()
{
	load_square_mesh();

	//load texture for wall
	
	//enemy_texture = load_texture("../Images/Starfish.png");
}

void load_healthbar()
{

	health_texture = load_texture("../Images/health.png");

}

void load_dirt_render()
{

	wall_texture = load_texture("../Images/Dirt1.png");

}

void load_texture_render()
{

	hook_texture = load_texture("../Images/Dirt1.png");
}

void load_character_render()
{

	character_texture = load_texture("../Images/Snowman.png");

}

void load_hook_render()
{

	hook_texture = load_texture("../Images/Dirt1.png");
}

void load_enemy_texture()
{


	enemy_texture = load_texture("../Images/Starfish.png");
}

void update_render_walls()
{
	Render render;

	for (Wall const &wall : walls)
	{
		render.pos = wall.position;
		render.x_scale = wall.scale;
		render.y_scale = wall.scale;
		render.pMesh = square_mesh;
		render.pTexture = wall_texture;
		render.dir = 0;

		draw_render(render);
	}


}


void update_health()
{
	Render render;
	
}

void update_render_character()
{
	Render render;
	render.pos = character->pos;
	render.x_scale = character->scale;
	render.y_scale = character->scale;
	render.pMesh = square_mesh;
	render.pTexture = character_texture;
	render.dir = 0; //TO update base on character movement

	draw_render(render);
}

void update_render_hook()
{
	if (hook->flag == true)
	{
		Render render;
		render.pos = hook->center_pos;
		render.x_scale = hook->scale;
		render.y_scale = hook->curr_len;
		render.pMesh = square_mesh; 
		render.pTexture = hook_texture;
		render.dir = hook->pivot_angle - PI/2; //TEMPORARY FIX , SHOULD NOT NEED TO ROTATE IT AGAIN :/

		draw_render(render);
	}
}



void update_render_enemy()
{
	Render render;
	for (Enemy const& enemy : enemies)
	{
		render.pos = enemy.pos;
		render.x_scale = enemy.scale;
		render.y_scale = enemy.scale;
		render.pMesh = square_mesh;
		render.pTexture = enemy_texture; //TO CHANGE !!!!, render based on the enemy type and its state
		render.dir = 0;

		draw_render(render);
	}
}


void draw_render(Render &render)
{

	AEMtx33	trans, scale, rot;

	// Compute the scalling matrix
	AEMtx33Scale(&scale, render.x_scale, render.y_scale);

	// Compute the rotational matrix
	AEMtx33Rot(&rot, render.dir);

	// Compute the translation matrix
	AEMtx33Trans(&trans, render.pos.x, render.pos.y);

	//Combining the matrix
	AEMtx33Concat(&render.transform, &rot, &scale);
	AEMtx33Concat(&render.transform, &trans, &render.transform);

	// Drawing object  - (first) - No tint
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);	// set to texture
	// No tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Set texture
	AEGfxTextureSet(render.pTexture, 0.0f, 0.0f); // Same object, different texture
	// Set transformation matrix
	AEGfxSetTransform(render.transform.m);
	// Draw the mesh
	AEGfxMeshDraw(render.pMesh, AE_GFX_MDM_TRIANGLES);

}

void unload_render()
{
	//unload texture
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (texturelist[i] != nullptr)
		{
			AEGfxTextureUnload(texturelist[i]);
		}
	}

	//free mesh
	AEGfxMeshFree(square_mesh);
	


}