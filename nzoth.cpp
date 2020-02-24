
#include "nzoth.h"
#include "main.h"
#include "input.h"
#include "sprite.h"
#include "table.h"
#include "collision.h"
#include "player.h"
#include "hole.h"

#define NZOTH_WIDTH	(32)
#define NZOTH_HEIGHT	(32)

#define ANIME_PATTERN_MAX		2
#define ANIME_PATTERN_SKIPFRAME 18
#define HOLE_SKIPFRAME 600


typedef struct
{
	D3DXVECTOR2 pos;			//�ʒu

	int			animePattern;	//�A�j���p�^�[��
	int			animeFrame;		//�p�^�[���؂�ւ��E�G�C�g

	CIRCLE		collision;		//�~�̓����蔻��
	int			hitpoint;		//�q�b�g�|�C���g

	D3DXVECTOR2 posTexture;

	bool		enable;
}NZOTH_DATA;

NZOTH_DATA nzoth;

void Nzoth_Initialize(void)
{
	//�v���C���[�̏�����
	nzoth.pos.x = SCREEN_WIDTH / 2;
	nzoth.pos.y = SCREEN_HEIGHT / 2;

	nzoth.collision.cx = nzoth.pos.x;
	nzoth.collision.cy = nzoth.pos.y;
	nzoth.collision.r = NZOTH_WIDTH * 0.8f;

	nzoth.hitpoint = 10;
	nzoth.animeFrame = 570;

	nzoth.enable = false;
}

void Nzoth_Finalize(void)
{

}

void Nzoth_Update(void)
{
	if (nzoth.enable)
	{
		D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);
		float s = 0.0f;

		dir = Player_GetPos() - nzoth.pos;
		s = sqrt(dir.x * dir.x + (dir.y * dir.y));
		if (s > 64.0f)
		{
			//���W���X�V����
			dir = dir / s;
			nzoth.pos += dir;
		}

		//�����蔻��p���W�̍X�V
		nzoth.collision.cx = nzoth.pos.x;
		nzoth.collision.cy = nzoth.pos.y;

		//�X�L�b�v����t���[���l�𒴂�����
		if (++nzoth.animeFrame % ANIME_PATTERN_SKIPFRAME == 0)
		{
			//�A�j���p�^�[����i�߂�(�ő�l�𒴂����烊�Z�b�g)
			if (++nzoth.animePattern >= ANIME_PATTERN_MAX)
				nzoth.animePattern = 0;
		}

		if (nzoth.animeFrame >= HOLE_SKIPFRAME)
		{
			Hole_Set(nzoth.pos);
			//�t���[���͌��ɖ߂�
			nzoth.animeFrame = 0;
		}
	}
}

void Nzoth_Draw(void)
{
	//�����t���O��TRUE�̓G�̂ݏ������s��
	if (nzoth.enable) {
		Sprite_Draw(TEXTURE_INDEX_NZOTH,
			nzoth.pos.x,
			nzoth.pos.y,
			nzoth.posTexture.x * 64,
			nzoth.posTexture.y * 64,
			32,
			32,
			16,
			16,
			1.5f,
			1.5f,
			0.0f);
	}
}

const CIRCLE* Nzoth_GetCollision()
{
	return &nzoth.collision;
}

void Nzoth_AddDamage(int damage)
{
	nzoth.hitpoint -= damage;
	if (nzoth.hitpoint <= 0)
	{
		nzoth.hitpoint = 0;
		nzoth.enable = false;
		Player_TargetCancel();
	}
}

int Nzoth_GetHitPoint()
{
	return nzoth.hitpoint;
}

D3DXVECTOR2* Nzoth_GetPospointer()
{
	return &nzoth.pos;
}

bool Nzoth_GetIsEnable()
{
	return nzoth.enable;
}

void Nzoth_Set(D3DXVECTOR2 pos)
{
	nzoth.pos.x = pos.x - 32.0f;
	nzoth.pos.y = pos.y + 32.0f;
	nzoth.enable = true;
}

void Nzoth_Texture(int animePattern)
{
	switch (animePattern)
	{
	case 0:
		nzoth.posTexture.x = 0.0f;
		break;
	case 1:
		nzoth.posTexture.x = 0.5f;
		break;
	default:
		break;
	}
}