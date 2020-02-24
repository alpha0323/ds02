#include "texture.h"
#include "player.h"
#include "boss.h"
#include "fade.h"
#include "scene.h"
#include "collision.h"
#include "explosion.h"
#include "score_draw.h"
#include "sprite.h"
#include "target.h"
#include "frostbolt.h"
#include "nzoth.h"
#include "hole.h"
#include "shadow.h"
#include "crack.h"
#include "valkyr.h"
#include "icelance.h"
#include "flurry.h"

typedef enum PHASE_INDEX
{
	PHASE_INDEX_FADE,
	PHASE_INDEX_PLAYER_IN,
	PHASE_INDEX_PLAYER_MUTEKI,
	PHASE_INDEX_PLAYER_NORMAL,
	PHASE_INDEX_STAGE_CLEAR,
	PHASE_INDEX_END,

	PHASE_INDEX_MAX
};

static PHASE_INDEX g_Phase;
static int g_GameFrameCount;

static int g_Score = 0;// 点数
static int g_KillCount = 0;


static bool Game_EndCheck(void);
static bool Game_Result;



void Game_Initialize(void)
{
	Player_Initialize();
	Boss_Initialize();
	Explosion_Initialize();
	Frostbolt_Initialize();
	Nzoth_Initialize();
	Hole_Initialize();
	Shadow_Initialize();
	Crack_Initialize();
	Valkyr_Initialize();
	Flurry_Initialize();

	g_Phase = PHASE_INDEX_FADE;
	g_GameFrameCount = 0;
	g_Score = 0;
	g_KillCount = 0;
	Fade_Start(false, 30, D3DCOLOR_RGBA(0,0,0,0));
}

void Game_Finalize(void)
{
	Player_Finalize();
	Boss_Finalize();
	Frostbolt_Finalize();
	Nzoth_Finalize();
	Hole_Finalize();
	Shadow_Finalize();
	Crack_Finalize();
	Icelance_Initialize();
}

void Game_Update(void)
{
	switch(g_Phase)
	{
	case PHASE_INDEX_FADE:
		if( !Fade_IsFade() ) {
			g_Phase = PHASE_INDEX_PLAYER_NORMAL;
			// PlaySound(SOUND_LABEL_BGM000);
		}
		break;
	case PHASE_INDEX_PLAYER_IN:
	case PHASE_INDEX_PLAYER_MUTEKI:
	case PHASE_INDEX_PLAYER_NORMAL:
		Player_Update();
		Boss_Update();
		Explosion_Update();
		Frostbolt_Update();
		Nzoth_Update();
		Hole_Update();
		Shadow_Update();
		Crack_Update();
		Valkyr_Update();
		Icelance_Update();
		Flurry_Update();

		//当たり判定は必ずすべてのアップデート処理が終わった後に行う
		Collision_Update();

		//ゲームの終了チェック
		if (Game_EndCheck())
		{
			Fade_Start(true, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_Phase = PHASE_INDEX_STAGE_CLEAR;
		}
		break;
	case PHASE_INDEX_STAGE_CLEAR:
		if (!Fade_IsFade()) {
			if (Game_Result)
				Scene_Change(SCENE_INDEX_RESULTCLEAR);
			else
				Scene_Change(SCENE_INDEX_RESULTOVER);
			g_Phase = PHASE_INDEX_END;
		}
		break;
	case PHASE_INDEX_END:
		break;
	}

}

void Game_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_PLATFORM,
		640,
		360,
		0,
		0,
		640,
		640,
		320,
		320,
		1.0f,
		1.0f,
		0.0f);

	Hole_Draw();
	Shadow_Draw();
	Crack_Draw();
	Sprite_Draw(TEXTURE_INDEX_GAME, 0.0f, 0.0f);
	Sprite_Draw(TEXTURE_INDEX_ICON, 32.0f, 32.0f);
	Player_Draw();
	Boss_Draw();
	Explosion_Draw();
	Score_Draw(0, 0, Player_GetHitPoint(), 7, true);
	Target_Draw();
	Frostbolt_Draw();
	Nzoth_Draw();
	Player_DrawCast();
	Player_DrawHP();
	Valkyr_Draw();
	Target_DrawHP();
	Icelance_Draw();
	Flurry_Draw();
}

bool Game_EndCheck(void)
{
	//15匹以上倒したら終了
	if (!Boss_IsEnable())
	{
		Game_Result = true;
		return true;
	}

	if (Player_GetHitPoint() <= 0)
	{
		Game_Result = false;
		return true;
	}

	return false;
}

void Game_AddScore(int score)
{
	g_Score += score;
}

void Game_AddKillCount()
{
	g_KillCount += 1;
}
