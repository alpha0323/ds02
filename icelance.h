#pragma once

#include "collision.h"

#define FROSTBOLT_CASTFRAME	108

void Icelance_Initialize(void);
void Icelance_Finalize(void);
void Icelance_Update(void);
void Icelance_Draw(void);
const CIRCLE* Icelance_GetCollision();

void Icelance_Cast(D3DXVECTOR2 player_pos, int target_number);