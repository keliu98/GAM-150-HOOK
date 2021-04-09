/*!*************************************************************************
****
\file enemy.h
\authors: Lau Yong Hui

\par DP email:  l.yonghui@digipen.edu
			
\par Course: CSD 1450
\par Project: Software Engineering Project 2
\date 160221


\brief
  This is a header file for  the enemy AI.
****************************************************************************/

#pragma once
#include "pch.h"

void enemy_move_L(size_t i);//move left function

void enemy_move_R(size_t i);//move right function

void enemy_idle(size_t i);//idle function

void enemy_jump(size_t i);// jump function

void skitter_AI(size_t);// Spider AI

void update_hook_attack();// update hook attack

void update_spikes();//