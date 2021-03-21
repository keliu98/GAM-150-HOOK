#pragma once

#include "pch.h"

//AEGfxVertexList* load_mesh(float size); //player

void load_dirt_render(); 

void load_dirt_render();

void load_texture_render();

void load_character_render();

void load_enemy_texture();

AEGfxTexture* load_texture(const char* image);

void load_character_render_right();

void load_character_render_left();

void load_character_render_jumpleft();

void load_character_render_jumpright();

void load_character_render_shootleft();

void load_character_render_shootright();

void load_character_render_swingleft();

void load_character_render_swingright();

void update_render_walls();
void update_render_buttons();
void update_render_character();
void update_render_hook();
void update_render_enemy();
void load_hook_render();
void load_button_texture();

void load_render();
void unload_render();





