#include "texture.h"
#include "fade.h"
#include "scene.h"
#include "collision.h"
#include "explosion.h"
#include "score_draw.h"


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

static bool Game_EndCheck(void);

void Game_Initialize(void)
{

	Explosion_Initialize();

	g_Phase = PHASE_INDEX_FADE;
	g_GameFrameCount = 0;
	Fade_Start(false, 30, D3DCOLOR_RGBA(0,0,0,0));
}

void Game_Finalize(void)
{
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

		Explosion_Update();

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
			Scene_Change(SCENE_INDEX_RESULT);
			g_Phase = PHASE_INDEX_END;
		}
		break;
	case PHASE_INDEX_END:
		break;
	}

}

void Game_Draw(void)
{

	Explosion_Draw();
	//Score_Draw(0, 0, Player_GetHitPoint(), 7, true);
}

bool Game_EndCheck(void)
{
	return false;
}