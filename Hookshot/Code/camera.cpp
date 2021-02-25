// Move the camera

#include "camera.h"

void camera_init() {
	AEGfxGetCamPosition(0, 0);
}


// scale to create a small bounding box for player
void camera_update(AEVec2 pos, float scale, AEVec2 velocity)
{
	AEGfxGetCamPosition(&pos.x, &pos.y);
	//if (AEInputCheckCurr(AEVK_W))
	//	AEGfxSetCamPosition(pos.x, pos.y + 2);
	//else if (AEInputCheckCurr(AEVK_S))
	//	AEGfxSetCamPosition(pos, pos - 2);

	//AEGfxGetCamPosition(&camX, &camY);
	//if (AEInputCheckCurr(AEVK_A))
	//	AEGfxSetCamPosition(camX - 2, camY);
	//else if (AEInputCheckCurr(AEVK_D))
	//	AEGfxSetCamPosition(camX + 2, camY);
}

