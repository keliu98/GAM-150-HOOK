/*!*************************************************************************
****
\file pch.h
\par Project: Hookshot
\authors: Tan Wei Wen (25%)
		  Egi Tan (25%)
		  Liu Ke (25%)
		  Yong Hui (25%)
\par DP email:  t.weiwen@digipen.edu
				egi.tan@digipen.edu
				ke.liu@digipen.edu
				l.yonghui@digipen.edu
\date 020221

\brief
This is a precompiled header file. Files listed below are compiled only 
once, improving build performance for future builds. This also affects 
IntelliSense performance, including code completion and many code browsing 
features. However, files listed here are ALL re-compiled if any one of 
them is updated between builds. Do not add files here that you will be 
updating frequently as this negates the performance advantage.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore. 
                All rights reserved.

****************************************************************************
***/

#ifndef PCH_H
#define PCH_H

/**************************************************************************/
/*!
	Below contains all the libraries used.
*/
/**************************************************************************/
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <memory>
#include "AEEngine.h"
#include "fmod.hpp"

/**************************************************************************/
/*!
	Below contains all file headers of game.
*/
/**************************************************************************/
#include "physics.h"
#include "extern.h"
#include "hook.h"
#include "Input.h"
#include "ObjectManager.h"
#include "Levels/Level1.h"
#include "Levels/Level2.h"
#include "Levels/Level3.h"
#include "Levels/Level4.h"
#include "Levels/Level5.h"
#include "menu.h"
#include "GameStateList.h"
#include "GameStateManager.h"
#include "camera.h"
#include "collision.h"
#include "newrendersystem.h"
#include "LoadMap.h"
#include "enemy.h"
#include "levelUI.h"
#include "music.h"
#include "intro.h"
#include "win.h"

#endif //PCH_H
