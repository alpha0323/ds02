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
	D3DXVECTOR2 pos;			//�ʒu
	D3DXVECTOR3	rot;			//�|���S���̉�]��
	D3DXVECTOR2*	targetPointer;	//�^�[�Q�b�g�|�C���^

	int			animeFrame;		//�p�^�[���؂�ւ��E�G�C�g

	CIRCLE		collision;		//�~�̓����蔻��
	int			damage;		//�q�b�g�|�C���g

	float			Radius;			// �|���S���̔��a
	float			BaseAngle;		// �|���S���̊p�x

	TextureIndex	texture;
	int			target;

	bool			isEnable;		//�L���t���O
}FLURRY;

FLURRY flurry[MAX_FLURRY];

void Flurry_Initialize(void)
{
	//�v���C���[�̏�����
	for (int i = 0; i < MAX_FLURRY; i++)
	{
		flurry[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		flurry[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		flurry[i].Radius = sqrt(FLURRY_WIDTH * FLURRY_WIDTH + FLURRY_HEIGHT * FLURRY_HEIGHT) / 2;
		flurry[i].BaseAngle = atan2(FLURRY_HEIGHT, FLURRY_WIDTH);

		//�L���t���O��OFF�ɂ���
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
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (flurry[i].isEnable == false)
			continue;

		//�������X�V����
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
				// �����G�t�F�N�g�̍쐬
				Explosion_Create(flurry[i].pos.x, flurry[i].pos.y);
				flurry[i].isEnable = false;
				break;
			case 2:
				Nzoth_AddDamage(flurry[i].damage);
				// �����G�t�F�N�g�̍쐬
				Explosion_Create(flurry[i].pos.x, flurry[i].pos.y);
				flurry[i].isEnable = false;
				break;
			case 3:
				Valkyr_AddDamage(flurry[i].damage);
				// �����G�t�F�N�g�̍쐬
				Explosion_Create(flurry[i].pos.x, flurry[i].pos.y);
				flurry[i].isEnable = false;
				break;
			default:
				break;
			}
			
		}

		//�p�x���X�V����
		flurry[i].rot.z = atan2(dir.y, dir.x);
		flurry[i].rot.z -= 1.5707963f;

		//���W���X�V����
		dir = 5 * dir / s;
		flurry[i].pos += dir;
	}
}

void Flurry_Draw(void)
{
	for (int i = 0; i < MAX_FLURRY; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
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

//�e�̎ˏo����
void Flurry_Cast(D3DXVECTOR2 player_pos, int target_number)
{
	for (int i = 0; i < MAX_FLURRY; i++) {
		//�e�̔z�񂩂�󂫂�T��
		//���ݎg���Ă���̈悾�����ꍇ��
		//�������Ȃ��ŃX���[����
		if (flurry[i].isEnable == true)
			continue;

		//���˂���ʒu���Z�b�g
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