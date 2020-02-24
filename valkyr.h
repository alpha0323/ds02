#pragma once

#include "collision.h"

#define VALKYR_HITPOINT	(100)

void Valkyr_Initialize(void);
void Valkyr_Finalize(void);
void Valkyr_Update(void);
void Valkyr_Draw(void);

const CIRCLE* Valkyr_GetCollision();
D3DXVECTOR2* Valkyr_GetPospointer();

bool Valkyr_GetIsEnable();
void Valkyr_AddDamage(int damage);

void Valkyr_Set(void);
void Valkyr_Texture(int animePattern);

void Valkyr_Catch(void);
int Valkyr_GetHitPoint();