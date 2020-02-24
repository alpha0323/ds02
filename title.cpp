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
	D3DXVECTOR2	posTextureJaina;	//JIANA�̃e�N�X�`�����W

	int	frame;			//�t���[��
	int	patternJaina;	//JIANA�̃p�^�[��
	int	patternPress;	//PRESS�̃p�^�[��

	bool end;	//�V�[���̏I��
	bool press;	//PRESS�̓_��

	void Scene_End();		//�V�[���̏I��
	void Parrern_Change();	//�p�^�[���̈ڍs
};

TITLE title;
SNOWFALL titleSnowfall;

//������
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

//�I������
void Title_Finalize(void)
{
}

//�X�V����
void Title_Update(void)
{
	//�V�[���̏I��
	title.Scene_End();

	//�p�^�[���̈ڍs
	title.Parrern_Change();

	//��̍X�V
	titleSnowfall.update();
}

//�`�揈��
void Title_Draw(void)
{
	//�^�C�g���̕`��
	Sprite_Draw(TEXTURE_INDEX_TITLE, 0.0f, 0.0f);

	//LOGO�̂̕`��
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

	//NEWS�̕`��
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

	//MSG�̕`��
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

	//JAINA�̕`��
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

	//PRESS�̕`��
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

	//��̕`��
	titleSnowfall.draw();
}

//�V�[���̏I��
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

//�p�^�[���̈ڍs
void TITLE::Parrern_Change() {
	//�X�L�b�v����t���[���l�𒴂�����
	if (++title.frame % JAINA_SKIPFRAME == 0)
	{
		//�p�^�[����i�߂�(�ő�l�𒴂����烊�Z�b�g)
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
		//�p�^�[����i�߂�(�ő�l�𒴂����烊�Z�b�g)
		if (++title.patternPress >= PRESS_PATTERN)
		{
			title.patternPress = 0;
			title.press = true;
		}
		else
		{
			title.press = false;
		}
		//�t���[���͌��ɖ߂�
		title.frame = 0;
	}
}