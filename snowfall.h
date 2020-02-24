#pragma once

#include "main.h"

//マクロ定義
#define SNOWFALL_MAX	(100)
#define SNOWFALL_START	(-10)
#define SNOWFALL_OVER	(740)
#define SNOWFALL_SKIP	(32)

//構造体定義
typedef struct {
	D3DXVECTOR2	pos;	//座標

	float	velocity;	//降り速度
	float	velocityR;	//角速度
	float	rotation;	//角度
	float	radius;		//半径

	bool	enable;
}SNOW;

//クラス定義
class SNOWFALL {
private:
	SNOW	snow[SNOWFALL_MAX];	//雪の構造体

	int	frame;	//フレーム
public:
	void initialize();	//初期化
	void finalize();	//終了処理
	void update();		//更新処理
	void draw();		//描画処理

	void set();
	void move();
};

//プロトタイプ宣言
void Snowfall_Initialize();	//初期化