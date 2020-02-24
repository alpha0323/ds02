#pragma once

#include "collision.h"
#include <d3dx9.h>

void Crack_Initialize(void);
void Crack_Finalize(void);
void Crack_Update(void);
void Crack_Draw(void);

const CIRCLE* Crack_GetCollision();
bool Crack_GetIsEnable();

void Crack_Set();
void Crack_Destroy();
D3DXVECTOR2 Crack_GetPos();