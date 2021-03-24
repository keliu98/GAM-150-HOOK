#pragma once

#include "pch.h"

//AEGfxVertexList* load_mesh(float size); //player

void load_bg_render();
void load_dirt_render();
void load_texture_render();
void load_character_render();
void load_enemy_texture();
void load_door_texture();
void load_hook_render();
void load_button_texture();

AEGfxTexture* load_texture(const char* image);

void update_render_door();
void update_render_bg();
void update_render_walls();
void update_render_buttons();
void update_render_character();
void update_render_hook();
void update_render_enemy();

void load_render();
void unload_render();