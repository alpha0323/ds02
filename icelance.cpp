#include "main.h"
#include "input.h"
#include "sprite.h"
#include "table.h"
#include "target.h"
#include "collision.h"
#include "icelance.h"
#include "boss.h"
#include "nzoth.h"
#include "explosion.h"
#include "valkyr.h"
#include "player.h"

#define ICELANCE_WIDTH	(32)
#define ICELANCE_HEIGHT	(32)

#define MAX_ICELANCE 10

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
}ICELANCE;

ICELANCE icelance[MAX_ICELANCE];

void Icelance_Initialize(void)
{
	//�v���C���[�̏�����
	for (int i = 0; i < MAX_ICELANCE; i++)
	{
		icelance[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		icelance[i].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		icelance[i].Radius = sqrt(ICELANCE_WIDTH * ICELANCE_WIDTH + ICELANCE_HEIGHT * ICELANCE_HEIGHT) / 2;
		icelance[i].BaseAngle = atan2(ICELANCE_HEIGHT, ICELANCE_WIDTH);

		//�L���t���O��OFF�ɂ���
		icelance[i].isEnable = false;
	}
}

void Icelance_Finalize(void)
{

}

void Icelance_Update(void)
{
	D3DXVECTOR2 dir = D3DXVECTOR2(0.0f, 0.0f);
	float s = 0.0f;

	for (int i = 0; i < MAX_ICELANCE; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (icelance[i].isEnable == false)
			continue;

		//�������X�V����
		dir = *icelance[i].targetPointer - icelance[i].pos;
		s = sqrt(dir.x * dir.x + (dir.y * dir.y));
		
		if (s < 32.0f)
		{
			switch (icelance[i].target)
			{
			case 0:
				icelance[i].isEnable = false;
				break;
			case 1:
				Boss_AddDamage(icelance[i].damage);
				// �����G�t�F�N�g�̍쐬
				Explosion_Create(icelance[i].pos.x, icelance[i].pos.y);
				icelance[i].isEnable = false;
				break;
			case 2:
				Nzoth_AddDamage(icelance[i].damage);
				// �����G�t�F�N�g�̍쐬
				Explosion_Create(icelance[i].pos.x, icelance[i].pos.y);
				icelance[i].isEnable = false;
				break;
			case 3:
				Valkyr_AddDamage(icelance[i].damage);
				// �����G�t�F�N�g�̍쐬
				Explosion_Create(icelance[i].pos.x, icelance[i].pos.y);
				icelance[i].isEnable = false;
				break;
			default:
				break;
			}
			
		}

		//�p�x���X�V����
		icelance[i].rot.z = atan2(dir.y, dir.x);

		//���W���X�V����
		dir = 5 * dir / s;
		icelance[i].pos += dir;
	}
}

void Icelance_Draw(void)
{
	for (int i = 0; i < MAX_ICELANCE; i++)
	{
		//�L���t���O��ON����Ȃ���Ή������Ȃ�
		if (icelance[i].isEnable == false)
			continue;
		Sprite_Draw(TEXTURE_INDEX_ICELANCE,
			icelance[i].pos.x,
			icelance[i].pos.y,
			0,
			0,
			32,
			32,
			16,
			16,
			1.0f,
			1.0f,
			icelance[i].rot.z);
	}
}

const CIRCLE* Icelance_GetCollision(int index)
{
	return &icelance[index].collision;
}

//�e�̎ˏo����
void Icelance_Cast(D3DXVECTOR2 player_pos, int target_number)
{
	for (int i = 0; i < MAX_ICELANCE; i++) {
		//�e�̔z�񂩂�󂫂�T��
		//���ݎg���Ă���̈悾�����ꍇ��
		//�������Ȃ��ŃX���[����
		if (icelance[i].isEnable == true)
			continue;

		//���˂���ʒu���Z�b�g
		icelance[i].pos = player_pos;
		icelance[i].target = target_number;
		icelance[i].targetPointer = Target_GetPospointer(target_number);
		icelance[i].damage = 2;
		if (Player_GetIntellect())
			icelance[i].damage += 2;
		icelance[i].isEnable = true;
		break;
	}
}