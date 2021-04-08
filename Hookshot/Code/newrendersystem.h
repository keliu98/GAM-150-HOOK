#pragma once

#include "pch.h"

//AEGfxVertexList* load_mesh(float size); //player
AEGfxTexture* load_texture(const char* image);

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

void update_render_guide(float x, float y);
void update_render_door();
void update_render_bg();
void update_render_walls();
void update_render_buttons();
void update_render_character();
void update_render_hook();
void update_render_enemy();
void update_render_credits();
void update_render_menubg();


void load_render();
void unload_render();


void load_character_render_right();
void load_character_render_left();
void load_character_render_jumpleft();
void load_character_render_jumpright();
void load_character_render_shootleft();
void load_character_render_shootright();
void load_character_render_swingleft();
void load_character_render_swingright();