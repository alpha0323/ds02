#pragma once

#include "collision.h"

#define FLURRY_CASTFRAME	156

void Flurry_Initialize(void);
void Flurry_Finalize(void);
void Flurry_Update(void);
void Flurry_Draw(void);
const CIRCLE* Flurry_GetCollision();

void Flurry_Cast(D3DXVECTOR2 player_pos, int target_number);