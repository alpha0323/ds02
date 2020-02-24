
#include "shadow.h"
#include "main.h"
#include "input.h"
#include "sprite.h"
#include "table.h"
#include "collision.h"
#include "player.h"
#include "crack.h"

#define SHADOW_WIDTH	(640)
#define SHADOW_HEIGHT	(640)

#define ANIME_PATTERN_MAX		2
#define ANIME_PATTERN_SKIPFRAME 120

typedef struct
{
	D3DXVECTOR2 pos;			//位置

	int			animePattern;	//アニメパターン
	int			animeFrame;		//パターン切り替えウエイト

	CIRCLE		collision;		//円の当たり判定
	float		Radius;			// ポリゴンの半径	

	bool		enable;
}SHADOW_DATA;

SHADOW_DATA shadow;

void Shadow_Initialize(void)
{
	//プレイヤーの初期化
	shadow.pos.x = SCREEN_WIDTH / 2;
	shadow.pos.y = SCREEN_HEIGHT / 2;

	shadow.collision.cx = shadow.pos.x;
	shadow.collision.cy = shadow.pos.y;
	shadow.collision.r = shadow.Radius;

	shadow.Radius = 0;

	shadow.enable = false;
}

void Shadow_Finalize(void)
{

}

void Shadow_Update(void)
{
	if (shadow.enable == false)
		return;
	if (++shadow.animeFrame >= ANIME_PATTERN_SKIPFRAME)
	{
		if (shadow.Radius >= 320)
		{
			D3DXVECTOR2 dir = Crack_GetPos() - Player_GetPos();
			float s = sqrt(dir.x * dir.x + (dir.y * dir.y));
			if (s > shadow.Radius + 32 || !Crack_GetIsEnable())
				Player_AddDamage(50);
			shadow.enable = false;
		}
		shadow.Radius += 16;
	}
}

void Shadow_Draw(void)
{
	if (shadow.enable == false)
		return;
	Sprite_Draw(TEXTURE_INDEX_SHADOW,
		shadow.pos.x,
		shadow.pos.y,
		0,
		0,
		SHADOW_WIDTH,
		SHADOW_HEIGHT,
		SHADOW_WIDTH / 2,
		SHADOW_HEIGHT / 2,
		shadow.Radius / (SHADOW_WIDTH / 2),
		shadow.Radius / (SHADOW_HEIGHT / 2),
		0.0f);
}

const CIRCLE* Shadow_GetCollision()
{
	return &shadow.collision;
}

bool Shadow_GetIsEnable()
{
	return shadow.enable;
}

void Shadow_Set()
{
	shadow.enable = true;
	shadow.animeFrame = 0;
	shadow.Radius = 32;
}

void Shadow_Destroy()
{
	shadow.enable = false;
}