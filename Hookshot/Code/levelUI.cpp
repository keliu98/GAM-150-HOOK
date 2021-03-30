#include "levelUI.h"

static char	font_to_use;


void PrintText(char* message, int type, AEVec2 position)	// italic or norm
{
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	if (type == NORMAL)
		font_to_use = font;
	else
		font_to_use = font_italic;

	AEGfxPrint(font_to_use, message, position.x, position.y, 1.0f, 1.f, 1.f, 1.f);
}