#pragma once

#include "main.h"

//�}�N����`
#define SNOWFALL_MAX	(100)
#define SNOWFALL_START	(-10)
#define SNOWFALL_OVER	(740)
#define SNOWFALL_SKIP	(32)

//�\���̒�`
typedef struct {
	D3DXVECTOR2	pos;	//���W

	float	velocity;	//�~�葬�x
	float	velocityR;	//�p���x
	float	rotation;	//�p�x
	float	radius;		//���a

	bool	enable;
}SNOW;

//�N���X��`
class SNOWFALL {
private:
	SNOW	snow[SNOWFALL_MAX];	//��̍\����

	int	frame;	//�t���[��
public:
	void initialize();	//������
	void finalize();	//�I������
	void update();		//�X�V����
	void draw();		//�`�揈��

	void set();
	void move();
};

//�v���g�^�C�v�錾
void Snowfall_Initialize();	//������