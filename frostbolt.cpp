#include "main.h"
#include "input.h"
#include "sprite.h"
#include "table.h"
#include "target.h"
#include "collision.h"
#include "frostbolt.h"
#include "boss.h"
#include "nzoth.h"
#include "explosion.h"
#include "valkyr.h"
#include "player.h"

#define FROSTBOLT_WIDTH	(32)
#define FROSTBOLT_HEIGHT	(32)

#define MAX_FROSTBOLT 10

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
}FROSTBOLT;

FROSTBOLT frostbolt[MAX_FROSTBOLT];

void Frostbolt_Initialize(void)
{
	//プレイヤーの初期化
	for (int i = 0; i < MAX_FROSTBOLT; i++)
	{
		frostbolt[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		frostbolt[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		frostbolt[i].Radius = sqrt(FROSTBOLT_WIDTH * FROSTBOLT_WIDTH + FROSTBOLT_HEIGHT * FROSTBOLT_HEIGHT) / 2;
		frostbolt[i].BaseAngle = atan2(FROSTBOLT_HEIGHT, FROSTBOLT_WIDTH);

		//有効フラグをOFFにする
		frostbolt[i].isEnable = false;
	}
}

void Frostbolt_Finalize(void)
{

}

void Frostbolt_Update(void)
{
	D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);
	float s = 0.0f;

	for (int i = 0; i < MAX_FROSTBOLT; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (frostbolt[i].isEnable == false)
			continue;

		//距離を更新する
		dir = *frostbolt[i].targetPointer - frostbolt[i].pos;
		s = sqrt(dir.x * dir.x + (dir.y * dir.y));
		
		if (s < 32.0f)
		{
			switch (frostbolt[i].target)
			{
			case 0:
				frostbolt[i].isEnable = false;
				break;
			case 1:
				Boss_AddDamage(frostbolt[i].damage);
				// 爆発エフェクトの作成
				Explosion_Create(frostbolt[i].pos.x, frostbolt[i].pos.y);
				frostbolt[i].isEnable = false;
				break;
			case 2:
				Nzoth_AddDamage(frostbolt[i].damage);
				// 爆発エフェクトの作成
				Explosion_Create(frostbolt[i].pos.x, frostbolt[i].pos.y);
				frostbolt[i].isEnable = false;
				break;
			case 3:
				Valkyr_AddDamage(frostbolt[i].damage);
				// 爆発エフェクトの作成
				Explosion_Create(frostbolt[i].pos.x, frostbolt[i].pos.y);
				frostbolt[i].isEnable = false;
				break;
			default:
				break;
			}
			
		}

		//角度を更新する
		frostbolt[i].rot.z = atan2(dir.y, dir.x);

		//座標を更新する
		dir = 5 * dir / s;
		frostbolt[i].pos += dir;
	}
}

void Frostbolt_Draw(void)
{
	for (int i = 0; i < MAX_FROSTBOLT; i++)
	{
		//有効フラグがONじゃなければ何もしない
		if (frostbolt[i].isEnable == false)
			continue;
		Sprite_Draw(TEXTURE_INDEX_FROSTBOLT,
			frostbolt[i].pos.x,
			frostbolt[i].pos.y,
			0,
			0,
			32,
			32,
			16,
			16,
			1.0f,
			1.0f,
			frostbolt[i].rot.z);
	}
}

const CIRCLE* Frostbolt_GetCollision(int index)
{
	return &frostbolt[index].collision;
}

//弾の射出処理
void Frostbolt_Cast(D3DXVECTOR2 player_pos, int target_number)
{
	for (int i = 0; i < MAX_FROSTBOLT; i++) {
		//弾の配列から空きを探す
		//現在使っている領域だった場合は
		//何もしないでスルーする
		if (frostbolt[i].isEnable == true)
			continue;

		//発射する位置をセット
		frostbolt[i].pos = player_pos;
		frostbolt[i].target = target_number;
		frostbolt[i].targetPointer = Target_GetPospointer(target_number);
		frostbolt[i].damage = 10;
		if (Player_GetIntellect())
			frostbolt[i].damage += 2;
		frostbolt[i].isEnable = true;
		break;
	}
}