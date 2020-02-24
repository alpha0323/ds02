
#include "valkyr.h"
#include "main.h"
#include "input.h"
#include "sprite.h"
#include "table.h"
#include "collision.h"
#include "player.h"
#include "hole.h"

#define VALKYR_WIDTH	(32)
#define VALKYR_HEIGHT	(32)

#define ANIME_PATTERN_MAX		2
#define ANIME_PATTERN_SKIPFRAME 18

typedef struct
{
	D3DXVECTOR2 pos;			//位置
	D3DXVECTOR3	rot;			//ポリゴンの回転量

	int			animePattern;	//アニメパターン
	int			animeFrame;		//パターン切り替えウエイト

	CIRCLE		collision;		//円の当たり判定
	int			hitpoint;		//ヒットポイント
	int			phase;

	D3DXVECTOR2 posTexture;

	bool		enable;
}VALKYR_DATA;

VALKYR_DATA valkyr;

void Valkyr_Initialize(void)
{
	//プレイヤーの初期化
	valkyr.pos.x = SCREEN_WIDTH / 2;
	valkyr.pos.y = SCREEN_HEIGHT / 2;

	valkyr.collision.cx = valkyr.pos.x;
	valkyr.collision.cy = valkyr.pos.y;
	valkyr.collision.r = VALKYR_WIDTH * 0.8f;

	valkyr.hitpoint = 60;
	valkyr.animeFrame = 570;

	valkyr.enable = false;
}

void Valkyr_Finalize(void)
{

}

void Valkyr_Update(void)
{
	if (valkyr.enable)
	{
		D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);
		float s = 0.0f;
		switch (valkyr.phase)
		{
		case 0:
			dir = Player_GetPos() - valkyr.pos;
			s = sqrt(dir.x * dir.x + (dir.y * dir.y));

			if (s > 10.0f)
			{
				//角度を更新する
				valkyr.rot.z = atan2(dir.y, dir.x) - (3.1415f / 2);
				//座標を更新する
				dir = 5 * dir / s;
				valkyr.pos += dir;
			}
			else
			{
				Player_Catch(1);
				valkyr.phase++;
			}
			break;
		case 1:
			dir = D3DXVECTOR2(640.0f, 360.0f) - valkyr.pos;
			s = sqrt(dir.x * dir.x + (dir.y * dir.y));

			if (s < 340.0f)
			{
				//角度を更新する
				valkyr.rot.z = (atan2(dir.y, dir.x) - (3.1415f / 2) + 3.1415f);
				//座標を更新する
				dir = 0.5 * dir / s;
				valkyr.pos -= dir;
			}
			else
				valkyr.phase++;

			if (valkyr.hitpoint > 50)
				Player_CatchPos(valkyr.pos);
			else
				Player_Catch(0);
			break;
		case 2:
			valkyr.hitpoint = 60;
			dir = valkyr.pos - D3DXVECTOR2(640.0f, 360.0f);
			valkyr.pos.x = cos(atan2(dir.y, dir.x) + 0.01f) * 320.0f + 640.0f;
			valkyr.pos.y = sin(atan2(dir.y, dir.x) + 0.01f) * 320.0f + 360.0f;
			//角度を更新する
			valkyr.rot.z = atan2(valkyr.pos.y - 360.0f, valkyr.pos.x - 640.0f);
			break;
		}

		//当たり判定用座標の更新
		valkyr.collision.cx = valkyr.pos.x;
		valkyr.collision.cy = valkyr.pos.y;
	}
}

void Valkyr_Draw(void)
{
	if (!valkyr.enable)
		return;
	Sprite_Draw(TEXTURE_INDEX_VALKYR,
		valkyr.pos.x,
		valkyr.pos.y,
		0,
		0,
		32,
		32,
		16,
		16,
		1.5f,
		1.5f,
		valkyr.rot.z);
}

const CIRCLE* Valkyr_GetCollision()
{
	return &valkyr.collision;
}

void Valkyr_AddDamage(int damage)
{
	valkyr.hitpoint -= damage;
	if (valkyr.hitpoint <= 50)
		valkyr.hitpoint = 50;
}

int Valkyr_GetHitPoint()
{
	return valkyr.hitpoint;
}

D3DXVECTOR2* Valkyr_GetPospointer()
{
	return &valkyr.pos;
}

bool Valkyr_GetIsEnable()
{
	return valkyr.enable;
}

void Valkyr_Set()
{
	valkyr.pos.x = 640.0f;
	valkyr.pos.y = 20.0f;
	valkyr.phase = 2;
	valkyr.hitpoint = 60;
	valkyr.enable = true;
}

void Valkyr_Catch()
{
	valkyr.phase = 0;
}