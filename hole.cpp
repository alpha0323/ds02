
#include "hole.h"
#include "main.h"
#include "input.h"
#include "sprite.h"
#include "table.h"
#include "collision.h"
#include "player.h"

#define HOLE_WIDTH	(360)
#define HOLE_HEIGHT	(360)

#define ANIME_PATTERN_MAX		2
#define ANIME_PATTERN_SKIPFRAME 60

typedef struct
{
	D3DXVECTOR2 pos;			//位置

	int			animePattern;	//アニメパターン
	int			animeFrame;		//パターン切り替えウエイト

	CIRCLE		collision;		//円の当たり判定
	float		Radius;			// ポリゴンの半径	

	bool		enable;
}HOLE_DATA;

HOLE_DATA hole[MAX_HOLE];

void Hole_Initialize(void)
{
	for (int i = 0; i < MAX_HOLE; i++)
	{
		//プレイヤーの初期化
		hole[i].pos.x = SCREEN_WIDTH / 2;
		hole[i].pos.y = SCREEN_HEIGHT / 2;

		hole[i].collision.cx = hole[i].pos.x;
		hole[i].collision.cy = hole[i].pos.y;
		hole[i].collision.r = hole[i].Radius;

		hole[i].Radius = 0;

		hole[i].enable = false;
	}
}

void Hole_Finalize(void)
{

}

void Hole_Update(void)
{
	for (int i = 0; i < MAX_HOLE; i++)
	{
		if (hole[i].enable == false)
			continue;
		if (++hole[i].Radius > HOLE_WIDTH / 2)
			hole[i].Radius = HOLE_WIDTH / 2;
		hole[i].collision.r = hole[i].Radius;
		if (++hole[i].animeFrame >= ANIME_PATTERN_SKIPFRAME)
		{
			hole[i].animeFrame = 0;
			D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);
			float s = 0.0f;
			dir = Player_GetPos() - hole[i].pos;
			s = sqrt(dir.x * dir.x + (dir.y * dir.y));
			if (s < hole[i].Radius + 32.0f)
			{
				Player_AddDamage(1);
				break;
			}
		}
	}
}

void Hole_Draw(void)
{
	for (int i = 0; i < MAX_HOLE; i++)
	{
		if (hole[i].enable == false)
			continue;
		Sprite_Draw(TEXTURE_INDEX_HOLE,
			hole[i].pos.x,
			hole[i].pos.y,
			0,
			0,
			360,
			360,
			180,
			180,
			hole[i].Radius / (HOLE_WIDTH / 2),
			hole[i].Radius / (HOLE_HEIGHT / 2),
			0.0f);
	}
}

const CIRCLE* Hole_GetCollision(int index)
{
	return &hole[index].collision;
}

bool Hole_GetIsEnable(int index)
{
	return hole[index].enable;
}

void Hole_Set(D3DXVECTOR2 pos)
{
	for (int i = 0; i < MAX_HOLE; i++)
	{
		if (hole[i].enable == true)
			continue;
		hole[i].pos = pos;
		hole[i].collision.cx = pos.x;
		hole[i].collision.cy = pos.y;
		hole[i].Radius = 0.0f;
		hole[i].animePattern = 0;
		hole[i].animeFrame = 0;
		hole[i].enable = true;
		break;
	}
}

void Hole_Destroy()
{
	for (int i = 0; i < MAX_HOLE; i++)
		hole[i].enable = false;
}