#pragma once

#include "pch.h"

//AEGfxVertexList* load_mesh(float size); //player

void load_dirt_render(); 

void load_dirt_render();

void load_texture_render();

void load_character_render();

void load_enemy_texture();

AEGfxTexture* load_texture(const char* image);

void update_render_walls();
void update_render_character();
void update_render_hook();
void update_render_enemy();
void load_hook_render();
void load_healthbar();

void load_render();
void unload_render();