#pragma once
#include "pch.h"

enum char_state {
	moving_left,
	moving_right,
	jumping,
	falling,
	idle,
	onhook

	//TODO Possible to cycle through the different states for multiple hooks ?
	//onhook2
	//onhook3
};

struct Hook {

	//TODO Position fired, Mouse position.
	//TODO Hook Position, when travelling.
	float radius;
	float velocity;
	float angle;
};

struct Character {
	float height;
	float width;

	//TODO Position
	//TODO Acceleration or Velocity ?
	
	float jump_strength;

	int char_state; // uses the enum char_state
	int lives;

	Hook* hook;
};


struct Wall {
	float height;
	float width;

	//TODO position
};

struct Button {
	float height;
	float width;

	//TODO position
};

struct Enemy {
	//TODO
};

