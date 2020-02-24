#pragma once

#include "collision.h"

#define BOSS_HITPOINT	(100)

#define Boss_COUNT 10

void Boss_Initialize(void);
void Boss_Finalize(void);
void Boss_Update(void);
void Boss_Draw(void);

D3DXVECTOR2* Boss_GetPospointer();
void Boss_AddDamage(int damage);
bool Boss_IsEnable();
void Boss_Texture(int animePattern);
int Boss_GetHitPoint();