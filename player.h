#pragma once

#include "collision.h"


void Player_Initialize(void);
void Player_Finalize(void);
void Player_Update(void);
void Player_Draw(void);
void Player_DrawCast(void);
const CIRCLE* Player_GetCollision();

void Player_AddDamage(int damage);
int Player_GetHitPoint();
int Player_GetTarget();
D3DXVECTOR2 Player_GetPos();

void Player_Texture(int muki, int animePattern);
void Player_TargetCancel(void);
void Player_Move(D3DXVECTOR2 crack_pos, int velocity);
void Player_DrawHP(void);
void Player_OutCheck(void);
void Player_CatchPos(D3DXVECTOR2 valkyr_pos);
void Player_Catch(int valkyr_catch);

bool Player_GetIntellect(void);