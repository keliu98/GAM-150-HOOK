// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here

#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <memory>

#include "AEEngine.h"
#include "physics.h"
#include "extern.h"
#include "hook.h"
#include "Input.h"

#include "ObjectManager.h"
#include "Levels/Level1.h"
#include "menu.h"
#include "GameStateList.h"
#include "GameStateManager.h"
#include "camera.h"
#include "collision.h"
#include "newrendersystem.h"
#include "LoadMap.h"


#endif //PCH_H
