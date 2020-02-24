#include "main.h"
#include "input.h"
#include "sprite.h"
#include "table.h"
#include "target.h"
#include "collision.h"
#include "flurry.h"
#include "boss.h"
#include "nzoth.h"
#include "explosion.h"
#include "valkyr.h"
#include "player.h"

#define FLURRY_WIDTH	(32)
#define FLURRY_HEIGHT	(32)

#define MAX_FLURRY 10

typedef struct
{
	D3DXVECTOR2 pos;			//位置
	D3DXVECTOR3	rot;			//ポリゴンの回転量
	D3DXVECTOR2*	targetPointer;	//ターゲットポインタ

	int			animeFrame;		//パターン切り替えウエイト

	CIRCLE		collision;		//円の当たり判定
	int			damage;		//ヒットポイント

	float			Radius;			// ポリゴンの半径
	float			BaseAngle;		// ポリゴンの角度

	TextureIndex	texture;
	int			target;

	bool			isEnable;		//有効フラグ
}FLURRY;

FLURRY flurry[MAX_FLURRY];

void Flurry_Initialize(void)
{
	//プレイヤーの初期化
	for (int i = 0; i < MAX_FLURRY; i++)
	{
		flurry[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		flurry[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		flurry[i].Radius = sqrt(FLURRY_WIDTH * FLURRY_WIDTH + FLURRY_HEIGHT * FLURRY_HEIGHT) / 2;
		flurry[i].BaseAngle = atan2(FLURRY_HEIGHT, FLURRY_WIDTH);

		//有効フラグをOFFにする
		flurry[i].isEnable = false;
	}
}

void Flurry_Finalize(void)
{

}

void Flurry_Update(void)
{
	D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);
	float s = 0.0f;

	for (int i = 0; i < MAX_FLURRY; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (flurry[i].isEnable == false)
			continue;

		//距離を更新する
		dir = *flurry[i].targetPointer - flurry[i].pos;
		s = sqrt(dir.x * dir.x + (dir.y * dir.y));
		
		if (s < 32.0f)
		{
			switch (flurry[i].target)
			{
			case 0:
				flurry[i].isEnable = false;
				break;
			case 1:
				Boss_AddDamage(flurry[i].damage);
				// 爆発エフェクトの作成
				Explosion_Create(flurry[i].pos.x, flurry[i].pos.y);
				flurry[i].isEnable = false;
				break;
			case 2:
				Nzoth_AddDamage(flurry[i].damage);
				// 爆発エフェクトの作成
				Explosion_Create(flurry[i].pos.x, flurry[i].pos.y);
				flurry[i].isEnable = false;
				break;
			case 3:
				Valkyr_AddDamage(flurry[i].damage);
				// 爆発エフェクトの作成
				Explosion_Create(flurry[i].pos.x, flurry[i].pos.y);
				flurry[i].isEnable = false;
				break;
			default:
				break;
			}
			
		}

		//角度を更新する
		flurry[i].rot.z = atan2(dir.y, dir.x);
		flurry[i].rot.z -= 1.5707963f;

		//座標を更新する
		dir = 5 * dir / s;
		flurry[i].pos += dir;
	}
}

void Flurry_Draw(void)
{
	for (int i = 0; i < MAX_FLURRY; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (flurry[i].isEnable == false)
			continue;
		Sprite_Draw(TEXTURE_INDEX_ICEEFFECT3,
			flurry[i].pos.x,
			flurry[i].pos.y,
			0,
			256,
			256,
			256,
			128,
			128,
			0.25f,
			0.25f,
			flurry[i].rot.z);
	}
}

const CIRCLE* Flurry_GetCollision(int index)
{
	return &flurry[index].collision;
}

//弾の射出処理
void Flurry_Cast(D3DXVECTOR2 player_pos, int target_number)
{
	for (int i = 0; i < MAX_FLURRY; i++) {
		//弾の配列から空きを探す
		//現在使っている領域だった場合は
		//何もしないでスルーする
		if (flurry[i].isEnable == true)
			continue;

		//発射する位置をセット
		flurry[i].pos = player_pos;
		flurry[i].target = target_number;
		flurry[i].targetPointer = Target_GetPospointer(target_number);
		flurry[i].damage = 12;
		if (Player_GetIntellect())
			flurry[i].damage += 2;
		flurry[i].isEnable = true;
		break;
	}
}