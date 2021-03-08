#pragma once

#include "pch.h"

AEGfxVertexList* load_mesh(float size); //player

AEGfxVertexList* load_hookmesh(); // hook

AEGfxTexture* load_texture(const char* image);

void draw_render1(AEVec2 Position, AEGfxVertexList* pMesh1, AEGfxTexture* pTex1);

void free_render(AEGfxVertexList* pMesh1, AEGfxTexture* pTex1);