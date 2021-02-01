#pragma once
#include "pch.h"

typedef void(*FP)(void);

extern std::fstream file;
extern int current, previous, next;

extern FP fpLoad, fpInitialize, fpUpdate, fpDraw, fpFree, fpUnload;

void GSM_Initialize(int startingState);
void GSM_Update();