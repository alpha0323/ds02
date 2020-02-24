#pragma once

#include <d3dx9.h>

void Target_Draw(void);
int Target_Search(int target);
D3DXVECTOR2* Target_GetPospointer(int target);
void Target_DrawHP(void);