#pragma once

#include "pch.h"

//------------------------------------
// Globals
extern float	g_dt;
extern double	g_appTime;

extern int      WINDOW_HEIGHT;
extern int      WINDOW_WIDTH;

//Physics
extern float    CHAR_HEIGHT_VEL;
extern const float GRAVITY;

//Fonts
extern char		font;
extern char		font_italic;

//For checking if game is paused and if to display credits
extern bool PAUSE;
extern bool display_credits;
extern bool display_tutorial;
extern bool confirm_state;

//To use for buttons
extern const float BUTTONSPACE_Y; //spacing to make it easier when arranging buttons

extern const int CONFIRM_QUIT; //The different states
extern const int FULLSCREEN;
extern const int SOUND;
extern const int TUTORIAL;
extern const int LEVELSELECT;
extern const int CREDITS;
extern const int OPTIONS;


