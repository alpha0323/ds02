
#include "crack.h"
#include "main.h"
#include "input.h"
#include "sprite.h"
#include "table.h"
#include "collision.h"
#include "player.h"

#define CRACK_WIDTH		(400)
#define CRACK_HEIGHT	(400)

#define ANIME_PATTERN_MAX		2
#define ANIME_PATTERN_SKIPFRAME 450

typedef struct
{
	D3DXVECTOR2 pos;			//位置

	int			animePattern;	//アニメパターン
	int			animeFrame;		//パターン切り替えウエイト

	CIRCLE		collision;		//円の当たり判定
	float		Radius;			// ポリゴンの半径	

	bool		enable;
}CRACK_DATA;

CRACK_DATA crack;

void Crack_Initialize(void)
{
	//プレイヤーの初期化
	crack.pos.x = SCREEN_WIDTH / 2;
	crack.pos.y = SCREEN_HEIGHT / 2;

	crack.collision.cx = crack.pos.x;
	crack.collision.cy = crack.pos.y;
	crack.collision.r = crack.Radius;

	crack.Radius = 0;

	crack.enable = false;
}

void Crack_Finalize(void)
{

}

void Crack_Update(void)
{
	if (crack.enable == false)
		return;
	if (++crack.animeFrame >= ANIME_PATTERN_SKIPFRAME)
		crack.enable = false;
	D3DXVECTOR2 dir = crack.pos - Player_GetPos();
	float s = sqrt(dir.x * dir.x + (dir.y * dir.y));
	if (s < crack.Radius + 32 || !crack.enable)
	{
		Player_Move(crack.pos, 1);
		if (crack.animeFrame % 60 == 0)
			Player_AddDamage(1);
	}
	
}

void Crack_Draw(void)
{
	if (crack.enable == false)
		return;
	Sprite_Draw(TEXTURE_INDEX_CRACK,
		crack.pos.x,
		crack.pos.y,
		0,
		0,
		CRACK_WIDTH,
		CRACK_HEIGHT,
		CRACK_WIDTH / 2,
		CRACK_HEIGHT / 2,
		crack.Radius / (CRACK_WIDTH / 2),
		crack.Radius / (CRACK_HEIGHT / 2),
		0.0f);
}

const CIRCLE* Crack_GetCollision()
{
	return &crack.collision;
}

bool Crack_GetIsEnable()
{
	return crack.enable;
}

void Crack_Set()
{
	crack.enable = true;
	crack.animeFrame = 0;
	crack.Radius = CRACK_WIDTH / 2;
	int crack_posSet = rand() % 4;
	switch (crack_posSet)
	{
	case 0:
		crack.pos.x = 640.0f;
		crack.pos.y = 20.0f;
		break;
	case 1:
		crack.pos.x = 640.0f;
		crack.pos.y = 700.0f;
		break;
	case 2:
		crack.pos.x = 300.0f;
		crack.pos.y = 320.0f;
		break;
	case 3:
		crack.pos.x = 980.0f;
		crack.pos.y = 320.0f;
		break;
	default:
		break;
	}
}

void Crack_Destroy()
{
	crack.enable = false;
}

D3DXVECTOR2 Crack_GetPos()
{
	return crack.pos;
}