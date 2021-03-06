#pragma once
#include "pch.h"

void physics_update();
void physics_intialize();

void set_accel_to_vel(AEVec2& vel, AEVec2 dir, float const accel);

void set_vel_to_pos(AEVec2& pos, AEVec2 dir, float &vel);
void set_vel_to_pos(AEVec2& pos, AEVec2& vel);

float create_vel_height(float height, float gravity);

void calculate_knockback(AEVec2& pos1, AEVec2& pos2, AEVec2& velocity, AEVec2 knockback);
