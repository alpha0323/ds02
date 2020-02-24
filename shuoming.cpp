#include "input.h"
#include "scene.h"
#include "sprite.h"
#include "texture.h"
#include "fade.h"
#include "shuoming.h"


void ShuoMing_Initialize(void)
{
	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void ShuoMing_Finalize(void)
{
}

void ShuoMing_Update(void)
{
	if( Keyboard_IsTrigger(DIK_RETURN) ) {
		Scene_Change(SCENE_INDEX_GAME);
	}
}

void ShuoMing_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_SHUOMING, 0.0f, 0.0f);
}
