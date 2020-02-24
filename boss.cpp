
#include "boss.h"
#include "main.h"
#include "sprite.h"
#include "table.h"
#include "player.h"
#include "explosion.h"
#include "nzoth.h"
#include "hole.h"
#include "shadow.h"
#include "crack.h"
#include "valkyr.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define BOSS_WIDTH				(32)
#define BOSS_HEIGHT				(32)
#define ANIME_PATTERN_MAX		(2)
#define ANIME_PATTERN_SKIPFRAME (16)
#define ANIME_SHADOW_SKIPFRAME	(1800)
#define ANIME_CRACK_SKIPFRAME	(675)

#define BOSS_SEARCH_RADIUS		(200.0f)
#define BOSS_SEARCH_ANGLE		(0.85f)
#define BOSS_CHASE_SPEED		(3.0f)
#define BOSS_RETURN_SPEED		(1.0f)

typedef struct
{
	int			enable;	//生存フラグ

	D3DXVECTOR2 pos;	//位置

	int			animePattern;	//アニメパターン
	int			animeFrame;		//パターン切り替えウエイト
	int			castFrame;
	D3DXVECTOR2 posTexture;

	CIRCLE		collision;
	int			hitpoint;
	int			phase;
}BOSS_DATA;

BOSS_DATA boss;

void Boss_Initialize(void)
{
	//敵の初期化
	boss.enable = true;
	boss.pos.x = SCREEN_WIDTH / 2;
	boss.pos.y = SCREEN_HEIGHT / 2;
	boss.animePattern = 0;
	boss.animeFrame = 0;
	boss.posTexture.x = 0.0f;
	boss.posTexture.y = 0.0f;
	boss.phase = 0;
	boss.hitpoint = 100;
}

void Boss_Finalize(void)
{

}

void Boss_Update(void)
{
	switch (boss.phase)
	{
	case 0:
		if (boss.hitpoint < 100)
		{
			Nzoth_Set(boss.pos);
			boss.phase++;
		}
		break;
	case 1:
		if (Nzoth_GetIsEnable() == false)
		{
			Hole_Destroy();
			Shadow_Set();
			Valkyr_Set();
			boss.castFrame = 0;
			boss.phase++;
		}
		break;
	case 2:
		if (++boss.castFrame >= ANIME_SHADOW_SKIPFRAME)
		{
			Shadow_Set();
			boss.castFrame = 0;
		}
		if (boss.castFrame == ANIME_CRACK_SKIPFRAME || boss.castFrame == ANIME_CRACK_SKIPFRAME + 900)
			Crack_Set();
		if (boss.castFrame == 300)
			Valkyr_Catch();
	default:
		break;
	}

	//当たり判定用座標の更新
	boss.collision.cx = boss.pos.x;
	boss.collision.cy = boss.pos.y;

	//スキップするフレーム値を超えたら
	if (++boss.animeFrame > ANIME_PATTERN_SKIPFRAME)
	{
		//アニメパターンを進める(最大値を超えたらリセット)
		if (++boss.animePattern >= ANIME_PATTERN_MAX)
			boss.animePattern = 0;
		//フレームは元に戻す
		boss.animeFrame = 0;
	}

	Boss_Texture(boss.animePattern);
}

void Boss_Draw(void)
{
	//生存フラグがTRUEの敵のみ処理を行う
	if (boss.enable) {
		Sprite_Draw(TEXTURE_INDEX_NZOTH,
			boss.pos.x,
			boss.pos.y,
			boss.posTexture.x * 64,
			boss.posTexture.y * 64,
			32,
			32,
			16,
			16,
			2.0f,
			2.0f,
			0.0f);
	}
}

void Boss_Destroy()
{
	Explosion_Create(boss.pos.x, boss.pos.y);
	boss.enable = false;
}

bool Boss_IsEnable()
{
	return boss.enable;
}

const CIRCLE* Boss_GetCollision()
{
	return &boss.collision;
}

D3DXVECTOR2* Boss_GetPospointer()
{
	return &boss.pos;
}

void Boss_AddDamage(int damage)
{
	if (boss.enable == true)
	{
		boss.hitpoint -= damage;
		if (boss.hitpoint <= 0)
			Boss_Destroy();
	}
}

void Boss_Texture(int animePattern)
{
	switch (animePattern)
	{
	case 0:
		boss.posTexture.x = 0.0f;
		break;
	case 1:
		boss.posTexture.x = 0.5f;
		break;
	default:
		break;
	}
}

int Boss_GetHitPoint()
{
	return boss.hitpoint;
}