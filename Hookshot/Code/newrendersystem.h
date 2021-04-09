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
  This source file contains the interface for all the character
  animation and rendering all the objects in the game. Functions are
  to be used by the different game states.

 \par Copyright: All content © 2021 Digipen Institute of Technology Singapore. All
				rights reserved.
****************************************************************************
***/

#pragma once

#include "pch.h"

//AEGfxVertexList* load_mesh(float size); //player
AEGfxTexture* load_texture(const char* image);

//Functions to load textures
void load_bg_render();
void load_dirt_render();
void load_texture_render();
void load_character_render();
void load_enemy_texture();
void load_door_texture();
void load_hook_render();
void load_button_texture();
void load_guide_texture();
void load_credits_render();
void load_menubg_render();
void load_spike_texture();

//Functions to draw the objects 
void update_render_guide(float x, float y);
void update_render_door();
void update_render_bg();
void update_render_walls();
void update_render_buttons();
void update_render_character();
void update_render_hook();
void update_render_enemy();
void update_render_credits(float x, float y);
void update_render_menubg();
void update_render_spikes();


//Loading and Unload of textures
void load_render();
void unload_render();

//Functions for animating the character.
void load_character_render_right();
void load_character_render_left();
void load_character_render_jumpleft();
void load_character_render_jumpright();
void load_character_render_shootleft();
void load_character_render_shootright();
void load_character_render_swingleft();
void load_character_render_swingright();


