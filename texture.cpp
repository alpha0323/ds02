#include <d3dx9.h>
//#include "debugPrintf.h"
#include "mydirect3d.h"
#include "texture.h"

#define TEXTURE_FILENAME_MAX (64)


typedef struct TextureFile_tag
{
	char filename[TEXTURE_FILENAME_MAX];
	int width;
	int height;
} TextureFile;

static const TextureFile g_TextureFiles[] = {
	{ "asset/texture/exp.png", 128, 128 },
	{ "asset/texture/number.tga", 320, 32 },
	{ "asset/texture/title.png", 1280, 720 },
	{ "asset/texture/result_clear.png", 1280, 720 },
	{ "asset/texture/result_over.png", 1280, 720 },
	{ "asset/texture/shuoming.png", 1280, 720 },
	{ "asset/texture/game_clear.png", 1280, 720 },
	{ "asset/texture/game_over.png", 1280, 720 },
	{ "asset/texture/jaina.png", 512, 512 },
	{ "asset/texture/nzoth.png", 64, 64 },
	{ "asset/texture/tmp.png", 1280, 720 },
	{ "asset/texture/cast.png", 200, 20 },
	{ "asset/texture/hole_blue2.png", 360, 360 },
	{ "asset/texture/hole_red.png", 640, 640 },
	{ "asset/texture/hole_pink.png", 400, 400 },
	{ "asset/texture/hole_blue.png", 640, 640 },
	{ "asset/texture/hitpoint.png", 200, 20 },
	{ "asset/texture/valkyr.png", 32, 32 },
	{ "asset/texture/frost_mage.png", 512, 512 },
	{ "asset/texture/press_enter.png", 512, 512 },
	{ "asset/texture/icon.png", 128, 128 },

	{ "asset/texture/frostbolt.png", 32, 32 },
	{ "asset/texture/ice_lance.png", 32, 32 },
	{ "asset/texture/ice_effect3.png", 512, 512 },
	{ "asset/texture/shiimmer.png", 32, 32 },
	{ "asset/texture/frost nova.png", 32, 32 },
	{ "asset/texture/time_warp.png", 32, 32 },
	{ "asset/texture/arcane_intellect.png", 32, 32 },
	{ "asset/texture/frozen_orb.png", 32, 32 },
	{ "asset/texture/ice_barrier.png", 32, 32 },
	{ "asset/texture/ice_block.png", 32, 32 },
};

static const int TEXTURE_FILE_COUNT = sizeof(g_TextureFiles) / sizeof(g_TextureFiles[0]);

static_assert(TEXTURE_INDEX_MAX == TEXTURE_FILE_COUNT, "TEXTURE_INDEX_MAX != TEXTURE_FILE_COUNT");

static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT] = {};

int Texture_Load(void)
{   
    LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if( !pDevice ) {
		return TEXTURE_FILE_COUNT;
	}

	int failed_count = 0;

	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( FAILED(D3DXCreateTextureFromFile(pDevice, g_TextureFiles[i].filename, &g_pTextures[i])) ) {
            // DebugPrintf("テクスチャの読み込みに失敗 ... %s\n", g_TextureFiles[i].filename);
			failed_count++;
		}
	}

	return failed_count;
}

void Texture_Release(void)
{
	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( g_pTextures[i] ) {
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_pTextures[index];
}

int Texture_GetWidth(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_TextureFiles[index].width;
}

int Texture_GetHeight(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_TextureFiles[index].height;
}
