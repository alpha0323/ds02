#include "input.h"
#include "scene.h"
#include "sprite.h"
#include "texture.h"
#include "fade.h"
#include "main.h"
#include "snowfall.h"

#define LOGO_POS_X	(100)
#define LOGO_POS_Y	(64)
#define LOGO_WIDTH	(512)
#define LOGO_HIGHT	(512)
#define LOGO_RATE	(0.375)

#define NEWS_POS_X	(192)
#define NEWS_POS_Y	(360)
#define NEWS_WIDTH	(512)
#define NEWS_HIGHT	(512)
#define NEWS_RATE	(0.75)

#define MSG_POS_X	(192)
#define MSG_POS_Y	(360)
#define MSG_WIDTH	(512)
#define MSG_HIGHT	(512)
#define MSG_RATE	(0.75)

#define JAINA_POS_X		(960)
#define JAINA_POS_Y		(360)
#define JAINA_WIDTH		(128)
#define JAINA_HIGHT		(128)
#define JAINA_RATE		(2)
#define JAINA_SKIPFRAME	(20)
#define JAINA_PATTERN	(2)

#define PRESS_POS_X		(640)
#define PRESS_POS_Y		(520)
#define PRESS_WIDTH		(512)
#define PRESS_HIGHT		(512)
#define PRESS_RATE		(0.75)
#define PRESS_SKIPFRAME	(60)
#define PRESS_PATTERN	(2)

class TITLE
{
public:
	D3DXVECTOR2	posTextureJaina;	//JIANAのテクスチャ座標

	int	frame;			//フレーム
	int	patternJaina;	//JIANAのパターン
	int	patternPress;	//PRESSのパターン

	bool end;	//シーンの終了
	bool press;	//PRESSの点滅

	void Scene_End();		//シーンの終了
	void Parrern_Change();	//パターンの移行
};

TITLE title;
SNOWFALL titleSnowfall;

//初期化
void Title_Initialize(void)
{
	title.posTextureJaina.x = 0;
	title.posTextureJaina.y = 0;

	title.frame = 0;
	title.patternJaina = 0;
	title.patternPress = 0;

	title.end = false;
	title.press = true;
}

//終了処理
void Title_Finalize(void)
{
}

//更新処理
void Title_Update(void)
{
	//シーンの終了
	title.Scene_End();

	//パターンの移行
	title.Parrern_Change();

	//雪の更新
	titleSnowfall.update();
}

//描画処理
void Title_Draw(void)
{
	//タイトルの描画
	Sprite_Draw(TEXTURE_INDEX_TITLE, 0.0f, 0.0f);

	//LOGOのの描画
	Sprite_Draw(TEXTURE_INDEX_TITLE_LOGO,
		LOGO_POS_X,
		LOGO_POS_Y,
		0,
		0,
		LOGO_WIDTH,
		LOGO_HIGHT,
		LOGO_WIDTH / 2,
		LOGO_HIGHT / 2,
		LOGO_RATE,
		LOGO_RATE,
		0.0f);

	//NEWSの描画
	Sprite_Draw(TEXTURE_INDEX_TITLE_NEWS,
		NEWS_POS_X,
		NEWS_POS_Y,
		0,
		0,
		NEWS_WIDTH,
		NEWS_HIGHT,
		NEWS_WIDTH / 2,
		NEWS_HIGHT / 2,
		NEWS_RATE,
		NEWS_RATE,
		0.0f);

	//MSGの描画
	Sprite_Draw(TEXTURE_INDEX_TITLE_MSG,
		MSG_POS_X,
		MSG_POS_Y,
		0,
		0,
		MSG_WIDTH,
		MSG_HIGHT,
		MSG_WIDTH / 2,
		MSG_HIGHT / 2,
		MSG_RATE,
		MSG_RATE,
		0.0f);

	//JAINAの描画
	Sprite_Draw(TEXTURE_INDEX_JAINA,
		JAINA_POS_X,
		JAINA_POS_Y,
		title.posTextureJaina.x,
		title.posTextureJaina.y,
		JAINA_WIDTH,
		JAINA_HIGHT,
		JAINA_WIDTH / 2,
		JAINA_HIGHT / 2,
		JAINA_RATE,
		JAINA_RATE,
		0.0f);

	//PRESSの描画
	if (title.press == true)
		Sprite_Draw(TEXTURE_INDEX_TITLE_PRESS,
			PRESS_POS_X,
			PRESS_POS_Y,
			0,
			0,
			PRESS_WIDTH,
			PRESS_HIGHT,
			PRESS_WIDTH / 2,
			PRESS_HIGHT / 2,
			PRESS_RATE,
			PRESS_RATE,
			0.0f);

	//雪の描画
	titleSnowfall.draw();
}

//シーンの終了
void TITLE::Scene_End()
{
	if (!title.end) {
		if (Keyboard_IsTrigger(DIK_SPACE)) {
			Fade_Start(true, 30, D3DCOLOR_RGBA(0, 0, 0, 0));
			title.end = true;
		}
	}
	else {
		if (!Fade_IsFade()) {
			Scene_Change(SCENE_INDEX_GAME);
		}
	}
}

//パターンの移行
void TITLE::Parrern_Change() {
	//スキップするフレーム値を超えたら
	if (++title.frame % JAINA_SKIPFRAME == 0)
	{
		//パターンを進める(最大値を超えたらリセット)
		switch (++title.patternJaina)
		{
		case 1:
			title.posTextureJaina.y = 128;
			break;
		default:
			title.posTextureJaina.y = 0;
			title.patternJaina = 0;
			break;
		}
	}

	if (title.frame >= PRESS_SKIPFRAME)
	{
		//パターンを進める(最大値を超えたらリセット)
		if (++title.patternPress >= PRESS_PATTERN)
		{
			title.patternPress = 0;
			title.press = true;
		}
		else
		{
			title.press = false;
		}
		//フレームは元に戻す
		title.frame = 0;
	}
}