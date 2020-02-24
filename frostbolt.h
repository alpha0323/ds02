#pragma once

#include "collision.h"

#define FROSTBOLT_CASTFRAME	108

void Frostbolt_Initialize(void);
void Frostbolt_Finalize(void);
void Frostbolt_Update(void);
void Frostbolt_Draw(void);
const CIRCLE* Frostbolt_GetCollision();

void Frostbolt_Cast(D3DXVECTOR2 player_pos, int target_number);