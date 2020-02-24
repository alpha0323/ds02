#include "input.h"
#include "scene.h"
#include "sprite.h"
#include "texture.h"
#include "fade.h"
#include "result_over.h"


void ResultOver_Initialize(void)
{
	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void ResultOver_Finalize(void)
{
}

void ResultOver_Update(void)
{
	if( Keyboard_IsTrigger(DIK_RETURN) ) {
		Scene_Change(SCENE_INDEX_TITLE);
	}
}

void ResultOver_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_RESULTOVER, 0.0f, 0.0f);
	Sprite_Draw(TEXTURE_INDEX_GAMEOVER, 0.0f, 0.0f);
}
