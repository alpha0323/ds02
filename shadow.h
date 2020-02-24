#pragma once

#include "collision.h"

void Shadow_Initialize(void);
void Shadow_Finalize(void);
void Shadow_Update(void);
void Shadow_Draw(void);

const CIRCLE* Shadow_GetCollision();
bool Shadow_GetIsEnable();

void Shadow_Set();
void Shadow_Destroy();