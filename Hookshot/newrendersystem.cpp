/*!*************************************************************************
****
\file GameStateManager.cpp
\authors: Tan Wei Wen
		  Egi Tan
		  Liu Ke
		  Yong Hui

\par DP email:  t.weiwen@digipen.edu
				egi.tan@digipen.edu
				ke.liu@digipen.edu
				l.yonghui@digipen.edu

\par Course: CSD 1450
\par Project: Software Engineering Project 2
\date 020221


\brief //TODO


****************************************************************************
***/

// ---------------------------------------------------------------------------
// includes	

#include "AEEngine.h"
#include "newrendersystem.h"



/******************************************************************************/
/*!
	Static Variables
*/
/******************************************************************************/

const unsigned int	GAME_OBJ_NUM_MAX = 32;			//The total number of different objects (Shapes)
static GameObj			sGameObjList[GAME_OBJ_NUM_MAX];
static unsigned long		sGameObjNum = 0;

GameObj* pObj;

AEGfxVertexList* pMesh1 = 0; // Pointer to Mesh (Model)
//  pointer to character texture
AEGfxTexture* pTex1;
AEGfxTexture* pTex2;
AEGfxTexture* pTex3;
AEGfxTexture* pTex4;


AEGfxVertexList* pMesh2 = 0; // Pointer to Mesh (Model)
// pointer to enemy texture
AEGfxTexture* pTex5;
AEGfxTexture* pTex6;
AEGfxTexture* pTex7;
AEGfxTexture* pTex8;


float obj1X = 0.0f, obj1Y = 0.0f; // Position variables for object 

float objtexX = 0, objtexY = 0;		// Texture variables for object 2 and 3 texture



GameObj load_render(const char* image)
{
	// load/create the mesh data (game objects / Shapes)


	// creating the objects(shapes)

	memset(sGameObjList, 0, sizeof(GameObj) * GAME_OBJ_NUM_MAX);

	pObj = sGameObjList + sGameObjNum++;
	// Informing the library about to use sprite to draw character running
	AEGfxMeshStart();
	// =====================
	// create the main character shape sprites
	// =====================
 

	// =====================
	// create the enemy shape sprite
	// =====================

	AEGfxMeshStart();

	// draw

	AEGfxTriAdd(
		-50.0f, -50.0f, 0xFFFF0000, 0.0f, 0.0f,
		35.5f, 00.0f, 0xFFFF0000, 0.0f, 0.0f,
		-50.0f, 50.0f, 0xFFFF0000, 0.0f, 0.0f);

	// saving the nesh in pMesh2
	pMesh2 = AEGfxMeshEnd();
	AE_ASSERT_MESG(pMesh2, "fail to create object!!");
	/*
	// load texture
	pTex5 = AEGfxTextureLoad("spriteimagesassets/bug1.png");	//load 1st from spritesheet

	// load second texture
	pTex6 = AEGfxTextureLoad("spriteimagesassets/bug2.png");	//load 2nd image from spritesheet

	// load thrid texture
	pTex7 = AEGfxTextureLoad("spriteimagesassets/bug3.png");	// load 3rd image from spritesheet

	// load fourth texture
	pTex8 = AEGfxTextureLoad("spriteimagesassets/bug4.png");	// load 3rd image from spritesheet
	*/
	// loading images end
	/////////////////////////

	// draw object
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// no tint
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Set Transparency
	AEGfxSetTransparency(1.0f);

}

void draw_render1(AEVec2* Position, AEGfxVertexList* pMesh1, AEGfxTexture* pTex1)
{

	// game loop draw
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEGfxSetPosition(0.0f, 0.0f);

	// Set position for object character
	AEGfxSetPosition(Position->x, Position->y);
	//No tinit
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);
	// No texture for object 1
	AEGfxTextureSet(pTex1, 0.0f, 0.0f);
	// Drawing the mesh (list of triangles)
	AEGfxMeshDraw(pMesh1, AE_GFX_MDM_TRIANGLES);

}



void free_render(AEGfxVertexList* pMesh1, AEGfxTexture* pTex1 )
{
	AEGfxMeshFree(pMesh1);
	AEGfxTextureUnload(pTex1);
}




