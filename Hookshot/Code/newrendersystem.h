#pragma once

#include "pch.h"

AEGfxVertexList* load_mesh(float size); //player

AEGfxTexture* load_texture(const char* image);

void update_render_walls();
void update_render_character();
void update_render_hook();

void load_render();
void unload_render();