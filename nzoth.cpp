
#include "nzoth.h"
#include "main.h"
#include "input.h"
#include "sprite.h"
#include "table.h"
#include "collision.h"
#include "player.h"
#include "hole.h"

#define NZOTH_WIDTH	(32)
#define NZOTH_HEIGHT	(32)

#define ANIME_PATTERN_MAX		2
#define ANIME_PATTERN_SKIPFRAME 18
#define HOLE_SKIPFRAME 600


typedef struct
{
	D3DXVECTOR2 pos;			//位置

	int			animePattern;	//アニメパターン
	int			animeFrame;		//パターン切り替えウエイト

	CIRCLE		collision;		//円の当たり判定
	int			hitpoint;		//ヒットポイント

	D3DXVECTOR2 posTexture;

	bool		enable;
}NZOTH_DATA;

NZOTH_DATA nzoth;

void Nzoth_Initialize(void)
{
	//プレイヤーの初期化
	nzoth.pos.x = SCREEN_WIDTH / 2;
	nzoth.pos.y = SCREEN_HEIGHT / 2;

	nzoth.collision.cx = nzoth.pos.x;
	nzoth.collision.cy = nzoth.pos.y;
	nzoth.collision.r = NZOTH_WIDTH * 0.8f;

	nzoth.hitpoint = 10;
	nzoth.animeFrame = 570;

	nzoth.enable = false;
}

void Nzoth_Finalize(void)
{

}

void Nzoth_Update(void)
{
	if (nzoth.enable)
	{
		D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);
		float s = 0.0f;

		dir = Player_GetPos() - nzoth.pos;
		s = sqrt(dir.x * dir.x + (dir.y * dir.y));
		if (s > 64.0f)
		{
			//座標を更新する
			dir = dir / s;
			nzoth.pos += dir;
		}

		//当たり判定用座標の更新
		nzoth.collision.cx = nzoth.pos.x;
		nzoth.collision.cy = nzoth.pos.y;

		//スキップするフレーム値を超えたら
		if (++nzoth.animeFrame % ANIME_PATTERN_SKIPFRAME == 0)
		{
			//アニメパターンを進める(最大値を超えたらリセット)
			if (++nzoth.animePattern >= ANIME_PATTERN_MAX)
				nzoth.animePattern = 0;
		}

		if (nzoth.animeFrame >= HOLE_SKIPFRAME)
		{
			Hole_Set(nzoth.pos);
			//フレームは元に戻す
			nzoth.animeFrame = 0;
		}
	}
}

void Nzoth_Draw(void)
{
	//生存フラグがTRUEの敵のみ処理を行う
	if (nzoth.enable) {
		Sprite_Draw(TEXTURE_INDEX_NZOTH,
			nzoth.pos.x,
			nzoth.pos.y,
			nzoth.posTexture.x * 64,
			nzoth.posTexture.y * 64,
			32,
			32,
			16,
			16,
			1.5f,
			1.5f,
			0.0f);
	}
}

const CIRCLE* Nzoth_GetCollision()
{
	return &nzoth.collision;
}

void Nzoth_AddDamage(int damage)
{
	nzoth.hitpoint -= damage;
	if (nzoth.hitpoint <= 0)
	{
		nzoth.hitpoint = 0;
		nzoth.enable = false;
		Player_TargetCancel();
	}
}

int Nzoth_GetHitPoint()
{
	return nzoth.hitpoint;
}

D3DXVECTOR2* Nzoth_GetPospointer()
{
	return &nzoth.pos;
}

bool Nzoth_GetIsEnable()
{
	return nzoth.enable;
}

void Nzoth_Set(D3DXVECTOR2 pos)
{
	nzoth.pos.x = pos.x - 32.0f;
	nzoth.pos.y = pos.y + 32.0f;
	nzoth.enable = true;
}

void Nzoth_Texture(int animePattern)
{
	switch (animePattern)
	{
	case 0:
		nzoth.posTexture.x = 0.0f;
		break;
	case 1:
		nzoth.posTexture.x = 0.5f;
		break;
	default:
		break;
	}
}