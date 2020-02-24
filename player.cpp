
#include "player.h"
#include "main.h"
#include "input.h"
#include "sprite.h"
#include "table.h"
#include "collision.h"
#include "target.h"
#include "frostbolt.h"
#include "icelance.h"
#include "flurry.h"
#include "explosion.h"

#define PLAYER_WIDTH	(32)
#define PLAYER_HEIGHT	(32)

#define ANIME_PATTERN_MAX		2
#define ANIME_PATTERN_SKIPFRAME 16

typedef struct
{
	D3DXVECTOR2 pos;			//位置
	D3DXVECTOR2	posTexture;		//
	int			muki;			//向き
	int			color;			//色

	int			animePattern;	//アニメパターン
	int			animeFrame;		//パターン切り替えウエイト

	CIRCLE		collision;		//円の当たり判定
	int			hitpoint;		//ヒットポイント

	int			target;
	int			cast;
	int			castFrame;
	int			castTarget;
	int			valkyrCatch;
	int			cooldown;
	int			shiimmer;
	float		radius;
	int			heal;
	int			healAll;
	float		timeWarp;
	int			timeWarpCD;
	int			intellect;
	int			iceBarrier;
	int			iceblock;
}PLAYER;

PLAYER player;

void Player_Initialize(void)
{
	//プレイヤーの初期化
	player.pos.x = SCREEN_WIDTH / 2;
	player.pos.y = (SCREEN_HEIGHT / 2) + 258.0f;

	player.posTexture.x = 0.0f;
	player.posTexture.y = 0.0f;

	player.color = 0;
	player.muki = 0;

	player.collision.cx = player.pos.x;
	player.collision.cy = player.pos.y;
	player.collision.r = PLAYER_WIDTH * 0.4f;

	player.hitpoint = 100;

	player.target = 0;
	player.cast = 0;
	player.valkyrCatch = 0;
	player.cooldown = 0;
	player.radius = 0.5f;
	player.heal = 0;
	player.timeWarp = 1;
	player.timeWarpCD = 0;
	player.intellect = -1;
	player.iceBarrier = 0;
	player.iceblock = 0;
}

void Player_Finalize(void)
{

}

void Player_Update(void)
{
	D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);

	if (player.iceblock >= 3300)
		Player_Catch(0);
	else 
	{
		if (Keyboard_IsPress(DIK_UP) || GamePad_IsPress(0, BUTTON_UP)) {
			dir.y -= 2.0f;
			player.muki = 2;
			player.cast = 0;
		}
		if (Keyboard_IsPress(DIK_DOWN) || GamePad_IsPress(0, BUTTON_DOWN)) {
			dir.y += 2.0f;
			player.muki = 0;
			player.cast = 0;
		}
		if (Keyboard_IsPress(DIK_LEFT) || GamePad_IsPress(0, BUTTON_LEFT)) {
			dir.x -= 2.0f;
			player.muki = 1;
			player.cast = 0;
		}
		if (Keyboard_IsPress(DIK_RIGHT) || GamePad_IsPress(0, BUTTON_RIGHT)) {
			dir.x += 2.0f;
			player.muki = 3;
			player.cast = 0;
		}
	}

	//TABが押されたら
	if (Keyboard_IsTrigger(DIK_TAB))
		player.target = Target_Search(player.target);

	//ESCが押されたら
	if (Keyboard_IsTrigger(DIK_ESCAPE) || GamePad_IsTrigger(0, BUTTON_A))
		player.target = 0;

	if (--player.timeWarpCD >= 3000)
	{
		player.timeWarp = 0.7f;
		player.radius = 1.0f;
	}
	else
	{
		player.timeWarp = 1.0f;
		player.radius = 0.5f;
	}
		
	if (--player.cooldown <= 0)
	{
		player.cooldown = 0;
		//1が押されたら弾を発射
		if (Keyboard_IsTrigger(DIK_1) && player.cast == 0) {
			if (player.target != 0)
			{
				player.castTarget = player.target;
				player.cast = 1;
				player.castFrame = FROSTBOLT_CASTFRAME * player.timeWarp;
				player.animePattern = 2;
				player.cooldown = 90 * player.timeWarp;
			}
		}

		//2が押されたら弾を発射
		if (Keyboard_IsTrigger(DIK_2) && player.cast == 0) {
			if (player.target != 0)
			{
				player.castTarget = player.target;
				player.cast = 2;
				player.castFrame = 0;
				player.animePattern = 2;
				player.cooldown = 90 * player.timeWarp;
			}
		}

		//3が押されたら弾を発射
		if (Keyboard_IsTrigger(DIK_3) && player.cast == 0) {
			if (player.target != 0)
			{
				player.castTarget = player.target;
				player.cast = 3;
				player.castFrame = FLURRY_CASTFRAME * player.timeWarp;
				player.animePattern = 2;
				player.cooldown = 90 * player.timeWarp;
			}
		}

		//4が押されたら弾を発射
		if (Keyboard_IsTrigger(DIK_4) && player.cast == 0 && player.shiimmer <= 0) {
			switch (player.muki)
			{
			case 0:
				dir.y += 160.0f;
				break;
			case 1:
				dir.x -= 160.0f;
				break;
			case 2:
				dir.y -= 160.0f;
				break;
			case 3:
				dir.x += 160.0f;
				break;
			default:
				break;
			}
			player.animePattern = 2;
			player.cooldown = 90 * player.timeWarp;
			player.shiimmer = 600 * player.timeWarp;
			// 爆発エフェクトの作成
			Explosion_Create(player.pos.x, player.pos.y);
		}

		//5が押されたら弾を発射
		if (Keyboard_IsTrigger(DIK_5) && player.cast == 0 && player.heal <= 0) {
			player.animePattern = 2;
			player.cooldown = 90 * player.timeWarp;
			player.heal = 600 * player.timeWarp;
			if (player.hitpoint + 10 > 100)
				player.hitpoint = 100;
			else
				player.hitpoint += 10;
			// 爆発エフェクトの作成
			Explosion_Create(player.pos.x, player.pos.y);
		}

		//6が押されたら弾を発射
		if (Keyboard_IsTrigger(DIK_6) && player.cast == 0 && player.timeWarpCD <= 0) {
			player.animePattern = 2;
			player.cooldown = 90 * player.timeWarp;
			player.timeWarpCD = 3600;
		}

		//7が押されたら弾を発射
		if (Keyboard_IsTrigger(DIK_7) && player.cast == 0) {
			player.animePattern = 2;
			player.cooldown = 90 * player.timeWarp;
			player.intellect = 3600;
		}

		//8が押されたら弾を発射
		if (Keyboard_IsTrigger(DIK_8) && player.cast == 0 && player.healAll <= 0) {
			player.animePattern = 2;
			player.cooldown = 90 * player.timeWarp;
			player.healAll = 3600 * player.timeWarp;
			player.hitpoint = 100;
			// 爆発エフェクトの作成
			Explosion_Create(player.pos.x, player.pos.y);
		}

		//9が押されたら弾を発射
		if (Keyboard_IsTrigger(DIK_9) && player.cast == 0 && player.iceBarrier <= 0) {
			player.animePattern = 2;
			player.cooldown = 90 * player.timeWarp;
			player.iceBarrier = 1800;
		}
		
		//10が押されたら弾を発射
		if (Keyboard_IsTrigger(DIK_0) && player.cast == 0 && player.iceblock <= 0) {
			player.animePattern = 2;
			player.cooldown = 90 * player.timeWarp;
			player.iceblock = 3600;
		}
	}

	if (--player.castFrame < 0 && player.cast != 0)
	{
		player.animePattern = 0;
		
		switch (player.cast)
		{
		case 1:
			Frostbolt_Cast(player.pos, player.castTarget);
			break;
		case 2:
			Icelance_Cast(player.pos, player.castTarget);
			break;
		case 3:
			Flurry_Cast(player.pos, player.castTarget);
			break;
		default:
			break;
		}

		player.cast = 0;
	}
	else if (player.cast == 0)
	{
		//スキップするフレーム値を超えたら
		if (++player.animeFrame > ANIME_PATTERN_SKIPFRAME)
		{
			//アニメパターンを進める(最大値を超えたらリセット)
			if (++player.animePattern >= ANIME_PATTERN_MAX)
				player.animePattern = 0;
			//フレームは元に戻す
			player.animeFrame = 0;
		}
	}
	else
	{
		D3DXVECTOR2 mukiCast = *Target_GetPospointer(player.castTarget) - player.pos;
		if (mukiCast.y > 0.0f && abs((int)mukiCast.x) <= abs((int)mukiCast.y))
		{
			player.muki = 0;
		}
		else if (mukiCast.x < 0.0f && abs((int)mukiCast.x) >= abs((int)mukiCast.y))
		{
			player.muki = 1;
		}
		else if (mukiCast.y < 0.0f && abs((int)mukiCast.x) <= abs((int)mukiCast.y))
		{
			player.muki = 2;
		}
		else if (mukiCast.x > 0.0f && abs((int)mukiCast.x) >= abs((int)mukiCast.y))
		{
			player.muki = 3;
		}
	}

	if (player.valkyrCatch == 0)
		// 座標の更新処理
		player.pos += dir;

	player.shiimmer--;
	player.heal--;
	player.intellect--;
	player.iceBarrier--;
	player.iceblock--;

	//当たり判定用座標の更新
	player.collision.cx = player.pos.x;
	player.collision.cy = player.pos.y;

	Player_Texture(player.muki, player.animePattern);

	Player_OutCheck();	
}

void Player_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_JAINA,
		player.pos.x,
		player.pos.y,
		player.posTexture.x * 512,
		player.posTexture.y * 512,
		128,
		128,
		64,
		64,
		player.radius,
		player.radius,
		0.0f);

	if (player.iceBarrier >= 1500)
	{
		Sprite_Draw(TEXTURE_INDEX_ICEBARRIER,
			player.pos.x,
			player.pos.y,
			0,
			0,
			32,
			32,
			16,
			16,
			player.radius * 3.0f,
			player.radius * 3.0f,
			0.0f);
	}

	if (player.iceblock >= 3300)
	{
		Sprite_Draw(TEXTURE_INDEX_ICEBLOCK,
			player.pos.x,
			player.pos.y,
			0,
			0,
			32,
			32,
			16,
			16,
			player.radius * 3.0f,
			player.radius * 3.0f,
			0.0f);
	}

	if (player.cooldown <= 0)
	{
		Sprite_Draw(TEXTURE_INDEX_FROSTBOLT, 444.0f, 684.0f);
		Sprite_Draw(TEXTURE_INDEX_ICELANCE, 484.0f, 684.0f);
		Sprite_Draw(TEXTURE_INDEX_ICEEFFECT3,
			544.0f,
			700.0f,
			0,
			256,
			256,
			256,
			128,
			128,
			0.125f,
			0.125f,
			0);

		if (player.shiimmer <=0)
			Sprite_Draw(TEXTURE_INDEX_SHIIMMER, 564.0f, 684.0f);
		if (player.heal <= 0)
			Sprite_Draw(TEXTURE_INDEX_FROSTNOVA, 604.0f, 684.0f);
		if (player.timeWarpCD <= 0)
			Sprite_Draw(TEXTURE_INDEX_TIMEWARP, 644.0f, 684.0f);
		Sprite_Draw(TEXTURE_INDEX_ICEEFFECT3,
			700.0f,
			700.0f,
			256,
			256,
			256,
			256,
			128,
			128,
			0.125f,
			0.125f,
			0);
		Sprite_Draw(TEXTURE_INDEX_FROZENORB, 724.0f, 684.0f);
		if (player.iceBarrier <= 0)
			Sprite_Draw(TEXTURE_INDEX_ICEBARRIER, 764.0f, 684.0f);
		if (player.iceblock <= 0)
			Sprite_Draw(TEXTURE_INDEX_ICEBLOCK, 804.0f, 684.0f);
	}
}

void Player_DrawCast(void)
{
	if (player.cast != 0)
	{
		int castFrameSkip = 0;
		switch (player.cast)
		{
		case 1:
			castFrameSkip = FROSTBOLT_CASTFRAME;
		case 3:
			castFrameSkip = FLURRY_CASTFRAME;
		default:
			break;
		}
		Sprite_Draw(TEXTURE_INDEX_CAST,
			32.0f,
			192.0f,
			0,
			0,
			200 * (castFrameSkip - player.castFrame) / castFrameSkip,
			20);
	}

	if (player.intellect >= 0)
		Sprite_Draw(TEXTURE_INDEX_ICEEFFECT3,
			48.0f,
			240.0f,
			256,
			256,
			256,
			256,
			128,
			128,
			0.125f,
			0.125f,
			0);
}

void Player_DrawHP(void)
{
	Sprite_Draw(TEXTURE_INDEX_HITPOINT,
		192.0f,
		64.0f,
		0,
		0,
		200 * (player.hitpoint) / 100,
		20);
}

const CIRCLE* Player_GetCollision()
{
	return &player.collision;
}

void Player_AddDamage(int damage)
{
	if (player.iceblock >= 3300)
		return;
	if (player.iceBarrier >= 1500)
		damage *= 0.5;
	player.hitpoint -= damage;
	if (player.hitpoint < 0)
		player.hitpoint = 0;
}

int Player_GetHitPoint()
{
	return player.hitpoint;
}

int Player_GetTarget()
{
	return player.target;
}

bool Player_GetIntellect()
{
	if (player.intellect >= 0)
		return true;
	return false;
}

void Player_Texture(int muki, int animePattern)
{
	switch (muki)
	{
	case 0:
		player.posTexture.x = 0.0f;
		break;
	case 1:
		player.posTexture.x = 0.25f;
		break;
	case 2:
		player.posTexture.x = 0.5f;
		break;
	case 3:
		player.posTexture.x = 0.75f;
		break;
	default:
		break;
	}
	switch (animePattern)
	{
	case 0:
		player.posTexture.y = 0.0f;
		break;
	case 1:
		player.posTexture.y = 0.25f;
		break;
	case 2:
		player.posTexture.y = 0.5f;
		break;
	default:
		break;
	}
}

D3DXVECTOR2 Player_GetPos()
{
	return player.pos;
}

void Player_TargetCancel(void)
{
	player.target = 0;
}

void Player_Move(D3DXVECTOR2 crack_pos, int velocity)
{
	D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);
	float s = 0.0f;

	dir = crack_pos - player.pos;
	s = sqrt(dir.x * dir.x + (dir.y * dir.y));
	if (s > 2.0f)
	{
		//座標を更新する
		dir = velocity * dir / s;
		player.pos += dir;
	}

	//当たり判定用座標の更新
	player.collision.cx = player.pos.x;
	player.collision.cy = player.pos.y;
}

void Player_OutCheck(void)
{
	D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);
	float s = 0.0f;

	dir = player.pos - D3DXVECTOR2(640.0f, 360.0f);
	s = sqrt(dir.x * dir.x + (dir.y * dir.y));

	if (s > 320.0f)
		player.hitpoint = 0;
}

void Player_CatchPos(D3DXVECTOR2 valkyr_pos)
{
	if (player.valkyrCatch == 1)
		player.pos = valkyr_pos;
}

void Player_Catch(int valkyr_catch)
{
	player.valkyrCatch = valkyr_catch;
}