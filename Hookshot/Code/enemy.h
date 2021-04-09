/*!*************************************************************************
****
\file enemy.cpp
\par Project: Hookshot
\authors: Yong Hui (85%)
		  Tan Wei Wen (15%)

\par DP email: l.yonghui@digipen.edu
			   t.weiwen@digipen.edu

\par Course: CSD 1450
\date 090421

\brief
This file contain the interface for the enemy behaviour and its interaction.

\par Copyright: All content © 2021 Digipen Institute of Technology Singapore.
				All rights reserved.

****************************************************************************
***/

#pragma once
#include "pch.h"

void enemy_move_L(size_t i);//move left function

void enemy_move_R(size_t i);//move right function

void enemy_idle(size_t i);//idle function

void enemy_jump(size_t i);// jump function

void skitter_AI(size_t);// Spider AI

void update_hook_attack();// update hook attack

void update_spikes();//