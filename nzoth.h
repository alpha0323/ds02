#pragma once

#include "collision.h"

#define NZOTH_HITPOINT	(100)

void Nzoth_Initialize(void);
void Nzoth_Finalize(void);
void Nzoth_Update(void);
void Nzoth_Draw(void);

const CIRCLE* Nzoth_GetCollision();
D3DXVECTOR2* Nzoth_GetPospointer();

bool Nzoth_GetIsEnable();
void Nzoth_AddDamage(int damage);

void Nzoth_Set(D3DXVECTOR2 pos);
void Nzoth_Texture(int animePattern);
int Nzoth_GetHitPoint();