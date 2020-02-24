#include "input.h"
#include "scene.h"
#include "sprite.h"
#include "texture.h"
#include "fade.h"
#include "result_clear.h"


void ResultClear_Initialize(void)
{
	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void ResultClear_Finalize(void)
{
}

void ResultClear_Update(void)
{
	if( Keyboard_IsTrigger(DIK_RETURN) ) {
		Scene_Change(SCENE_INDEX_TITLE);
	}
}

void ResultClear_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_RESULTCLEAR, 0.0f, 0.0f);
	Sprite_Draw(TEXTURE_INDEX_GAMECLEAR, 0.0f, 0.0f);
}
