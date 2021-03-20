
#include "pch.h"

//globals for tracking texture
static const int MAX_TEXTURE = 20;
AEGfxTexture* texturelist[MAX_TEXTURE];
int texture_count;

//Pointer to square mesh
AEGfxVertexList* square_mesh;

//Pointer to the wall texture
AEGfxTexture* wall_texture;

//Pointer to the character texture running right
AEGfxTexture* character_texture;

//Pointer to the character texture running left
AEGfxTexture* character_texture1;

//Pointer to the character texture jumping left
AEGfxTexture* character_texture2;

//Pointer to the character texture jumping left
AEGfxTexture* character_texture3;

//Pointer to the character texture throw left
AEGfxTexture* character_texture4;

//Pointer to the character texture throw right
AEGfxTexture* character_texture5;

//Pointer to the hook texture
AEGfxTexture* hook_texture;

//Pointer to the hook texture
AEGfxTexture* enemy_texture;

// counter to swap textures;
int counter = 0;

struct Render
{
	AEVec2 pos;
	AEGfxVertexList* pMesh;
	AEGfxTexture* pTexture;

	float dir;
	float x_scale;
	float y_scale;

	float x_offset{0};
	float y_offset{0};

	float x_offset1{ 0 };
	float y_offset1{ 0 };

	float x_offset2{ 0 };
	float y_offset2{ 0 };

	float x_offset3{ 0 };
	float y_offset3{ 0 };

	AEMtx33 transform;
};

void draw_render(Render& render);

void load_square_mesh()
{

	AEGfxMeshStart();

	AEGfxTriAdd(
		0.5, 0.5, 0x00FFFFFF, 0.5f, 0.0f,
		-0.5, 0.5, 0x00FFFFFF, 0.0f, 0.0f,
		-0.5, -0.5, 0x00FFFFFF, 0.0f, 0.5f);

	AEGfxTriAdd(
		-0.5, -0.5, 0x00FF00FF, 0.0f, 0.5f,
		0.5, -0.5, 0x00FFFF00, 0.5f, 0.5f,
		0.5, 0.5, 0x0000FFFF, 0.5f, 0.0f);




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

void load_dirt_render()
{
	wall_texture = load_texture("../Images/Dirt1.png");

}

void load_texture_render()
{
	hook_texture = load_texture("../Images/Dirt1.png");
}

void load_character_render_right()
{
	// run in the right direction
	character_texture = load_texture("../Images/4testimages.png");

}

void load_character_render_left()
{
	// run in the left direction
	character_texture1 = load_texture("../Images/4testimagesreverse.png");
}

void load_character_render_jumpleft()
{
	// jump in the left direction
	character_texture2 = load_texture("../Images/4testimagesjumpleft.png");

}

void load_character_render_jumpright()
{
	// jump in the right direction
	character_texture3 = load_texture("../Images/4testimagesjump.png");

}

void load_character_render_shootleft()
{
	// shoot hook in left direction
	character_texture4 = load_texture("../Images/4testimagesthrowleft.png");

}

void load_character_render_shootright()
{
	// shoot hook in right direction
	character_texture5 = load_texture("../Images/4testimagesthrow.png");

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

void update_render_character()
{
	Render render;
	render.pos = character->pos;
	render.x_scale = character->scale;
	render.y_scale = character->scale;
	render.pMesh = square_mesh;
	render.pTexture = character_texture;	//load character running right/left
	render.dir = 0; //TO update base on character movement

	if (AEInputCheckCurr(AEVK_D))
	{
		render.pTexture = character_texture;	// load character run right
		render.x_offset = 0.0;
		render.y_offset = 0.0;

		render.x_offset1 = 0.5;
		render.y_offset1 = 0.0;

		render.x_offset2 = 0.0;
		render.y_offset2 = 0.5;

		render.x_offset3 = 0.5;
		render.y_offset3 = 0.5;

		draw_render(render);
	}

	 if (AEInputCheckCurr(AEVK_A))
	{
		render.pTexture = character_texture1;	// load character run left

		render.x_offset = 0.0;
		render.y_offset = 0.0;

		render.x_offset1 = 0.5;
		render.y_offset1 = 0.0;

		render.x_offset2 = 0.0;
		render.y_offset2 = 0.5;

		render.x_offset3 = 0.5;
		render.y_offset3 = 0.5;

		draw_render(render);
	
	}
	 if (AEInputCheckCurr(AEVK_W))
	 {
		 render.pTexture = character_texture2;	// load character jump right

		 render.x_offset = 0.0;
		 render.y_offset = 0.0;

		 render.x_offset1 = 0.5;
		 render.y_offset1 = 0.0;

		 render.x_offset2 = 0.0;
		 render.y_offset2 = 0.5;

		 render.x_offset3 = 0.5;
		 render.y_offset3 = 0.5;

		 draw_render(render);
	 }
	 /*
	
	 */
	 	

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
	AEGfxTextureSet(render.pTexture, render.x_offset, render.y_offset);  // Same object, different texture
	++counter;
	if (counter < 240 )
		AEGfxTextureSet(render.pTexture, render.x_offset1, render.y_offset1);  // Same object, different texture
	else if ( counter < 480 )
		AEGfxTextureSet(render.pTexture, render.x_offset2, render.y_offset2);  // Same object, different texture
	else if ( counter < 720 )
		AEGfxTextureSet(render.pTexture, render.x_offset3, render.y_offset3);  // Same object, different texture
	else if ( counter < 960 )
		AEGfxTextureSet(render.pTexture, render.x_offset2, render.y_offset2);  // Same object, different texture
	else
	{
		AEGfxTextureSet(render.pTexture, render.x_offset, render.y_offset);  // Same object, different texture
		counter = 0;
	}
	



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