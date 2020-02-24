#pragma once

#include "collision.h"

#define MAX_HOLE 100

void Hole_Initialize(void);
void Hole_Finalize(void);
void Hole_Update(void);
void Hole_Draw(void);

const CIRCLE* Hole_GetCollision(int index);
bool Hole_GetIsEnable(int index);

void Hole_Set(D3DXVECTOR2 pos);
void Hole_Destroy();