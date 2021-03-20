#pragma once

#include "pch.h"

//AEGfxVertexList* load_mesh(float size); //player

void load_dirt_render(); 

void load_dirt_render();

void load_texture_charrender();

void load_texture_render();

void load_character_render_right();

void load_character_render_left();

void load_character_render_jumpleft();

void load_character_render_jumpright();

void load_character_render_shootright();

void load_character_render_shootleft();

void load_enemy_texture();

AEGfxTexture* load_texture(const char* image);

void update_render_walls();
void update_render_character();
void update_render_hook();
void update_render_enemy();
void load_hook_render();

void load_render();
void unload_render();