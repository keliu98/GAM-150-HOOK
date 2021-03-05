#pragma once

#include "AEEngine.h"

struct GameObj
{
	AEGfxVertexList* pMesh1;		// hold the shapes
	AEGfxTexture* pTex;		// hold the textures
}typedef GameObj;

GameObj load_render(const char * image); //player

void draw_render1( AEVec2* Position, AEGfxVertexList* pMesh1, AEGfxTexture* pTex1);

void free_render(AEGfxVertexList* pMesh1, AEGfxTexture* pTex1);
