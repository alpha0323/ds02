#include "input.h"
#include "scene.h"
#include "sprite.h"
#include "texture.h"
#include "fade.h"
#include <d3d9.h>
#include "main.h"
#include "title.h"

static bool g_bEnd = false;

#define JAINA_WIDTH		(64)
#define JAINA_HEIGHT	(64)

#define ANIME_PATTERN_MAX		2
#define ANIME_PATTERN_SKIPFRAME 16

#define PRESS_PATTERN_MAX		2
#define PRESS_PATTERN_SKIPFRAME 120

#define JAINA_POS_X		(640)
#define JAINA_POS_Y		(512)

typedef struct
{
	D3DXVECTOR2	posTextureJaina;
	D3DXVECTOR2	posTextureNzoth;

	int			animePattern;	//アニメパターン
	int			animeFrame;		//パターン切り替えウエイト

	int			pressPattern;	//アニメパターン
	int			pressFrame;		//パターン切り替えウエイト
}TITLE;

TITLE title;

void Title_Initialize(void)
{
	g_bEnd = false;

	title.posTextureJaina.x = 0.0f;
	title.posTextureJaina.y = 0.0f;
	title.posTextureNzoth.x = 0.0f;
	title.posTextureNzoth.y = 0.0f;

	title.animePattern = 0;
	title.animeFrame = 0;
}

void Title_Finalize(void)
{
}

void Title_Update(void)
{
	if( !g_bEnd ) { 
		if( Keyboard_IsTrigger(DIK_RETURN) ) {
			Fade_Start(true, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
			g_bEnd = true;
		}
	}
	else{
		if( !Fade_IsFade() ) {
			Scene_Change(SCENE_INDEX_SHUOMING);
		}
	}

	//スキップするフレーム値を超えたら
	if (++title.animeFrame > ANIME_PATTERN_SKIPFRAME)
	{
		//アニメパターンを進める(最大値を超えたらリセット)
		if (++title.animePattern >= ANIME_PATTERN_MAX)
			title.animePattern = 0;
		//フレームは元に戻す
		title.animeFrame = 0;
	}

	//スキップするフレーム値を超えたら
	if (++title.pressFrame > PRESS_PATTERN_SKIPFRAME)
	{
		//アニメパターンを進める(最大値を超えたらリセット)
		if (++title.pressPattern >= PRESS_PATTERN_MAX)
			title.pressPattern = 0;
		//フレームは元に戻す
		title.pressFrame = 0;
	}

	Texture_Set(title.animePattern);
}

void Title_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_TITLE, 0.0f, 0.0f);

	Sprite_Draw(TEXTURE_INDEX_JAINA,
		JAINA_POS_X,
		JAINA_POS_Y,
		title.posTextureJaina.x * 512,
		title.posTextureJaina.y * 512,
		128,
		128,
		64,
		64,
		1.5f,
		1.5f,
		0.0f);

	Sprite_Draw(TEXTURE_INDEX_FROSTMAGE,
		640,
		128,
		0,
		0,
		512,
		512,
		258,
		258,
		1.0f,
		1.0f,
		0.0f);

	if (title.pressPattern == 0)
		Sprite_Draw(TEXTURE_INDEX_PRESSENTER,
			640,
			360,
			0,
			0,
			512,
			512,
			258,
			258,
			1.0f,
			1.0f,
			0.0f);
}

void Texture_Set(int animePattern)
{
	switch (animePattern)
	{
	case 0:
		title.posTextureJaina.y = 0.0f;
		title.posTextureNzoth.x = 0.0f;
		break;
	case 1:
		title.posTextureJaina.y = 0.25f;
		title.posTextureNzoth.x = 0.5f;
		break;
	default:
		break;
	}
}