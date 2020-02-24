#pragma once

#include <d3d9.h>

typedef enum 
{
	TEXTURE_INDEX_EXPLOSION,
	TEXTURE_INDEX_NUMBER,
	TEXTURE_INDEX_JAINA,
	TEXTURE_INDEX_SNOWFALL,

	TEXTURE_INDEX_TITLE,
	TEXTURE_INDEX_TITLE_LOGO,
	TEXTURE_INDEX_TITLE_NEWS,
	TEXTURE_INDEX_TITLE_MSG,
	TEXTURE_INDEX_TITLE_PRESS,

	TEXTURE_INDEX_GAME,
	TEXTURE_INDEX_RESULT,

    TEXTURE_INDEX_MAX
}TextureIndex;

int Texture_Load(void); //èâä˙âª
void Texture_Release(void); //èIóπèàóù
LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index);
int Texture_GetWidth(TextureIndex index);
int Texture_GetHeight(TextureIndex index);
