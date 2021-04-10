/*!*************************************************************************
****
\file newrendersystem.cpp
\authors: Liu Ke (70%)
		  Tan Wei Wen (10%)
		  Egi Tan (10%)
		  Yong Hui (10%)
		  

\par DP email:  t.weiwen@digipen.edu
				egi.tan@digipen.edu
				l.yonghui@digipen.edu
				ke.liu@digipen.edu

\par Course: CSD 1450
\date 020221

\brief
  This source file contains the implementation for all the character
  animation and rendering all the objects in the game

 \par Copyright: All content © 2021 Digipen Institute of Technology Singapore. All
				rights reserved.
****************************************************************************
***/


#include "pch.h"

//globals for tracking texture
static const int MAX_TEXTURE = 20;
AEGfxTexture* texturelist[MAX_TEXTURE];
int texture_count;

//Pointer to square mesh
AEGfxVertexList* square_mesh;

//Pointer to the wall texture
AEGfxTexture* wall_texture_top;
AEGfxTexture* wall_texture_bot;

//Pointer to the character texture
AEGfxTexture* character_texture;


// -------------ADDED CODE FROM LIU KE MERGE------------------------
//Pointer to the character texture at static left
AEGfxTexture* character_texture00;
//Pointer to the character texture running right
AEGfxTexture* character_texture0;
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
//Pointer to the character texture swing left
AEGfxTexture* character_texture6;
//Pointer to the character texture swing right
AEGfxTexture* character_texture7;

//Pointer to the hook texture
AEGfxTexture* hook_texture;

//Pointer to the enemy texture
AEGfxTexture* enemy_texture;

//Pointer to the enemy texture other dir 
//AEGfxTexture* enemy_texture1;

// Pointer to button
AEGfxTexture* button_texture[2];

//Pointer to background
AEGfxTexture* bg;

//Pointer to door
AEGfxTexture* door;

//Pointer to credits texture
AEGfxTexture* credits;

//Pointer to tutorial texture
AEGfxTexture* tutorial;

//Pointer to tutorial texture
AEGfxTexture* menu_bg;


// counter to swap textures;
int counter = 0;

//Pointer to square mesh
AEGfxVertexList* animation_mesh;
// -------------ADDED CODE FROM LIU KE MERGE------------------------

//Pointer to door
AEGfxTexture* guides;

AEGfxTexture* spike_texture;


struct Render
{
	AEVec2 pos{0, 0};
	AEGfxVertexList* pMesh{nullptr};
	AEGfxTexture* pTexture{nullptr};

	float dir{0};
	float x_scale{0};
	float y_scale{0};


	float x_offset{ 0 };
	float y_offset{ 0 };
	float x_offset1{ 0 };
	float y_offset1{ 0 };
	float x_offset2{ 0 };
	float y_offset2{ 0 };
	float x_offset3{ 0 };
	float y_offset3{ 0 };


	AEMtx33 transform{0,0};
};

//Forward Declarations
void draw_render(Render& render);
void draw_animation_render(Render& render);

void load_square_mesh()
{
	// create square mesh for the map 
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

void load_animation_mesh()
{

	// create mesh for the animation characters
	AEGfxMeshStart();
	AEGfxTriAdd(
		0.5, 0.5, 0x00FFFFFF, 0.5f, 0.0f,
		-0.5, 0.5, 0x00FFFFFF, 0.0f, 0.0f,
		-0.5, -0.5, 0x00FFFFFF, 0.0f, 0.5f);
	AEGfxTriAdd(
		-0.5, -0.5, 0x00FF00FF, 0.0f, 0.5f,
		0.5, -0.5, 0x00FFFF00, 0.5f, 0.5f,
		0.5, 0.5, 0x0000FFFF, 0.5f, 0.0f);
	animation_mesh = AEGfxMeshEnd();
	AE_ASSERT_MESG(square_mesh, "Failed to create mesh 1!!");
}

// loading of textures
AEGfxTexture* load_texture(const char* image)
{

	AEGfxTexture* pTex1st = AEGfxTextureLoad(image);
	AE_ASSERT_MESG(pTex1st, "Failed to create texture!!");
	texturelist[texture_count] = pTex1st;
	texture_count++;

	return pTex1st;
}


// rendering textures functions
void load_render()
{
	load_square_mesh();
	load_animation_mesh();
}


// create button textures
void load_button_texture()
{


	button_texture[0] = load_texture("../Images/Button1.png"); //change this during merge
	button_texture[1] = load_texture("../Images/Button2.png"); //change this during merge
}

// background image render
void load_bg_render()
{
	bg = load_texture("../Images/Background_2.png");
}

// ground render
void load_dirt_render()
{
	wall_texture_top = load_texture("../Images/Floor1_3.png");
	wall_texture_bot = load_texture("../Images/Floor2_2.png");
}

// load second ground render
void load_texture_render()
{
	hook_texture = load_texture("../Images/Floor2_2.png");
}

// create hook render 
void load_hook_render()
{
	hook_texture = load_texture("../Images/Floor2_2.png");
}

// create enemy texture
void load_enemy_texture()
{
	enemy_texture = load_texture("../Images/skitter.png");
}


// create door or exit texture
void load_door_texture()
{
	door = load_texture("../Images/Door.png");
}

//create character render  animation
void load_character_render()
{
	character_texture = load_texture("../Images/4testimagesstart.png");
}


void load_character_left()
{
	character_texture00 = load_texture("../Images/4testimagesstartleft.png");
}
void load_character_render_right()
{
	// run in the right direction
	character_texture0 = load_texture("../Images/4testimagesfortest.png");
}
void load_character_render_left()
{
	// run in the left direction
	character_texture1 = load_texture("../Images/4testimagesfortest left.png");
}
void load_character_render_jumpleft()
{
	// jump in the left direction
	character_texture2 = load_texture("../Images/4testimagesjumpleft.png");
}
void load_character_render_jumpright()
{
	// jump in the right direction
	character_texture3 = load_texture("../Images/4testimagesjump.png");		//image jump right
}
void load_character_render_shootleft()
{
	// shoot hook in left direction
	character_texture4 = load_texture("../Images/4testimagesthrowleft.png");
}
void load_character_render_shootright()
{
	// shoot hook in right direction
	character_texture5 = load_texture("../Images/4testimagesreverse.png");

}
void load_character_render_swingright()
{
	// shoot hook in right direction
	character_texture6 = load_texture("../Images/4testimageswiningright.png");
}
void load_character_render_swingleft()
{
	// shoot hook in right direction
	character_texture7 = load_texture("../Images/4testimageswiningleft.png");
}

// credit page render image
void load_credits_render()
{
	credits = load_texture("../Images/Credits.png");
}

// guide render images
void load_guide_texture()
{
	guides = load_texture("../Images/Guides.png");
}

// menu image
void load_menubg_render()
{
	menu_bg = load_texture("../Images/Title.png");

}

// spike render texture
void load_spike_texture()
{
	spike_texture = load_texture("../Images/Spikes.png");
}

// update render guide
void update_render_guide(float x, float y)
{
	Render render;

	// make it translate left a bit -? for later
	render.pos = {x, y};
	render.x_scale = (float)(WINDOW_WIDTH * 2);
	render.y_scale = (float)(WINDOW_HEIGHT * 2 + 50);
	render.pMesh = square_mesh;
	render.pTexture = guides;
	render.dir = 0;

	draw_render(render);
}

// update of rendering door function
void update_render_door()
{
	Render render;
	static float scale_x = 40.0f * 5.0f, scale_y = 40.0f * 6.0f;
	static AEVec2 door_pos = *end_position;

	render.pos = { door_pos.x - (40.0f * 2.0f), door_pos.y - (40.0f * 2.0f) };
	render.x_scale = scale_x;
	render.y_scale = scale_y;
	render.pMesh = square_mesh;
	render.pTexture = door;
	render.dir = 0;

	draw_render(render);
}

// update the rendering credits 
void update_render_credits(float x, float y)
{
	Render render;

	render.pos = { x, y };
	render.x_scale = 800.0f;
	render.y_scale = 1000.0f;
	render.pMesh = square_mesh;
	render.pTexture = credits;
	render.dir = 0;

	draw_render(render);
}

// update render menu function
void update_render_menubg()
{
	Render render;
	static float scale_x = (float)WINDOW_WIDTH, scale_y = (float)WINDOW_HEIGHT;

	// make it translate left a bit -? for later
	render.pos = { 0,0 };
	render.x_scale = scale_x;
	render.y_scale = scale_y;
	render.pMesh = square_mesh;
	render.pTexture = menu_bg;
	render.dir = 0;

	draw_render(render);
}


void update_render_bg()
{
	Render render;
	static float scale_x = (float)WINDOW_WIDTH, scale_y = (float)WINDOW_HEIGHT;

	// make it translate left a bit -? for later
	render.pos = center_point();
	render.x_scale  = scale_x;
	render.y_scale = scale_y;
	render.pMesh = square_mesh;
	render.pTexture = bg;
	render.dir = 0;

	draw_render(render);

	// debug cam
	// draw_cam_bounding_box(render.pTexture);
}

//update render wall function
void update_render_walls()
{
	Render render;

	for (Wall const &wall : walls)
	{
		render.pos = wall.position;
		render.x_scale = wall.scale;
		render.y_scale = wall.scale;
		render.pMesh = square_mesh;
		if (wall.type == 1)
			render.pTexture = wall_texture_top;
		else
			render.pTexture = wall_texture_bot;
		render.dir = 0;

		draw_render(render);
	}
}

// update render spikes function
void update_render_spikes()
{
	Render render;

	for (Spike const& spike : spikes)
	{
		render.pos = spike.position;
		render.x_scale = spike.scale;
		render.y_scale = spike.scale;
		render.pMesh = square_mesh;
		render.pTexture = spike_texture;
		render.dir = 0;

		draw_render(render);
	}
}

// update render button function
void update_render_buttons()//change this during merge
{
	Render render;

	for (Button const& button : buttons)
	{
		render.pos = button.pos_trans;
		render.x_scale = button.scale.x;
		render.y_scale = button.scale.y;
		render.pMesh = square_mesh;
		if (button.highlight == false)
			render.pTexture = button_texture[0];
		else
			render.pTexture = button_texture[1];



		render.dir = 0;
		draw_render(render);

		// drawing the font 
		
		static char text[100];
		memset(text, 0, 100 * sizeof(char));
		sprintf_s(text, button.string);
		PrintText(text, NORMAL, button.pos_ratio);
	}
}

// update the rendering of the character function
void update_render_character()
{
	Render render;
	render.pos = character->pos;
	render.x_scale = character->scale;
	render.y_scale = character->scale;
	render.pMesh = animation_mesh;



	render.dir = 0; //TO update base on character movement

	if (AEInputCheckPrev(AEVK_D))
	{
		render.pTexture = character_texture;	// load character face right
	}
	//else if (AEInputCheckReleased(AEVK_A))
	//{
	//	render.pTexture = character_texture00;	// load character face left
	//}
	else
	{
		render.pTexture = character_texture;	// load character face right
	}
	//render.pTexture = character_texture;
	render.dir = 0; //TO update base on character movement
	//draw_render(render);
	if (AEInputCheckCurr(AEVK_D))
	{
		render.pTexture = character_texture0;	// load character run right
		render.x_offset = 0.0;
		render.y_offset = 0.0;
		render.x_offset1 = 0.5;
		render.y_offset1 = 0.0;
		render.x_offset2 = 0.0;
		render.y_offset2 = 0.5;
		render.x_offset3 = 0.5;
		render.y_offset3 = 0.5;
		if (AEInputCheckCurr(AEVK_W))
		{
			render.pTexture = character_texture3;	// load character jump right
			render.x_offset = 0.0;
			render.y_offset = 0.0;
			render.x_offset1 = 0.5;
			render.y_offset1 = 0.0;
			render.x_offset2 = 0.0;
			render.y_offset2 = 0.5;
			render.x_offset3 = 0.5;
			render.y_offset3 = 0.5;
		}

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
		if (AEInputCheckCurr(AEVK_W))
		{
			render.pTexture = character_texture2;	// load character jump left
			render.x_offset = 0.0;
			render.y_offset = 0.0;
			render.x_offset1 = 0.5;
			render.y_offset1 = 0.0;
			render.x_offset2 = 0.0;
			render.y_offset2 = 0.5;
			render.x_offset3 = 0.5;
			render.y_offset3 = 0.5;
		}


	}
	if (AEInputCheckCurr(AEVK_W))
	{
		render.pTexture = character_texture3;	// load character run right
		render.x_offset = 0.0;
		render.y_offset = 0.0;
		render.x_offset1 = 0.5;
		render.y_offset1 = 0.0;
		render.x_offset2 = 0.0;
		render.y_offset2 = 0.5;
		render.x_offset3 = 0.5;
		render.y_offset3 = 0.5;
	}
	if (AEInputCheckCurr(AEVK_LBUTTON))
	{
		render.pTexture = character_texture5;	// load character shoot
		render.x_offset = 0.0;
		render.y_offset = 0.0;
		render.x_offset1 = 0.5;
		render.y_offset1 = 0.0;
		render.x_offset2 = 0.0;
		render.y_offset2 = 0.5;
		render.x_offset3 = 0.5;
		render.y_offset3 = 0.5;

		if (AEInputCheckCurr(AEVK_D))
		{
			render.pTexture = character_texture6;	// load character swing right
			render.x_offset = 0.0;
			render.y_offset = 0.0;
			render.x_offset1 = 0.5;
			render.y_offset1 = 0.0;
			render.x_offset2 = 0.0;
			render.y_offset2 = 0.5;
			render.x_offset3 = 0.5;
			render.y_offset3 = 0.5;
		}
		else if (AEInputCheckCurr(AEVK_A))
		{
			render.pTexture = character_texture7;	// load character swing left
			render.x_offset = 0.0;
			render.y_offset = 0.0;
			render.x_offset1 = 0.5;
			render.y_offset1 = 0.0;
			render.x_offset2 = 0.0;
			render.y_offset2 = 0.5;
			render.x_offset3 = 0.5;
			render.y_offset3 = 0.5;
		}
	}


	if (character->counter == 0)
	{
		draw_animation_render(render);
	}
	else if ((character->counter % 5) == 0)
	{
		draw_animation_render(render);
	}
	
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

// update rendering enemy movement function
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


// drawing of texture 
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

	//For the texture to blend into the game.
	AEGfxSetTransparency(1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
}

// offset the textures to create animations
void draw_animation_render(Render& render)
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
	if (counter < 3)
		AEGfxTextureSet(render.pTexture, render.x_offset1, render.y_offset1);  // Same object, different texture
	else if (counter < 6)
		AEGfxTextureSet(render.pTexture, render.x_offset2, render.y_offset2);  // Same object, different texture
	else if (counter < 9)
		AEGfxTextureSet(render.pTexture, render.x_offset3, render.y_offset3);  // Same object, different texture
	else if (counter < 12)
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

	//For the texture to blend into the game.
	AEGfxSetTransparency(1.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
}


// unload or free the texture
void unload_render()
{
	//unload texture
	for (int i = 0; i < MAX_TEXTURE; i++)
	{
		if (texturelist[i] != nullptr)
		{
			AEGfxTextureUnload(texturelist[i]);
			texturelist[i] = nullptr;//change this during merge
			texture_count--;
		}
	}

	//free mesh
	AEGfxMeshFree(square_mesh);
	AEGfxMeshFree(animation_mesh);
}