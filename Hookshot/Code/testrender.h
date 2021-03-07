#pragma once
#pragma once

#include "pch.h"

void load_mesh(); //player

void load_hookmesh(); // hook

void load_texture(const char* image);

void draw_render1(AEVec2 Position, AEGfxVertexList* pMesh1, AEGfxTexture* pTex1);

void free_render(AEGfxVertexList* pMesh1, AEGfxTexture* pTex1);
