#include "scene.h"
#include "title.h"
#include "game.h"
#include "result_clear.h"
#include "result_over.h"
#include "shuoming.h"

static SCENE_INDEX g_SceneIndex;
static SCENE_INDEX g_SceneNextIndex;

typedef void (*SceneFunc)(void);

static const SceneFunc Initialize[] = {
	Title_Initialize,
	ShuoMing_Initialize,
	Game_Initialize,
	ResultClear_Initialize,
	ResultOver_Initialize,
};


void Scene_Initialize(SCENE_INDEX index)
{
	g_SceneNextIndex = g_SceneIndex = index;
	
	Initialize[g_SceneIndex]();
}

void Scene_Finalize(void)
{
	switch( g_SceneIndex ) {

	case SCENE_INDEX_TITLE:
		Title_Finalize();
		break;

	case SCENE_INDEX_SHUOMING:
		ShuoMing_Finalize();
		break;

	case SCENE_INDEX_GAME:
		Game_Finalize();
		break;

	case SCENE_INDEX_RESULTCLEAR:
		ResultClear_Finalize();
		break;

	case SCENE_INDEX_RESULTOVER:
		ResultOver_Finalize();
		break;
	}
}

void Scene_Update(void)
{
	switch( g_SceneIndex ) {

	case SCENE_INDEX_TITLE:
		Title_Update();
		break;

	case SCENE_INDEX_SHUOMING:
		ShuoMing_Update();
		break;

	case SCENE_INDEX_GAME:
		Game_Update();
		break;

	case SCENE_INDEX_RESULTCLEAR:
		ResultClear_Update();
		break;

	case SCENE_INDEX_RESULTOVER:
		ResultOver_Update();
		break;
	}
}

void Scene_Draw(void)
{
	switch( g_SceneIndex ) {

	case SCENE_INDEX_TITLE:
		Title_Draw();
		break;

	case SCENE_INDEX_SHUOMING:
		ShuoMing_Draw();
		break;

	case SCENE_INDEX_GAME:
		Game_Draw();
		break;

	case SCENE_INDEX_RESULTCLEAR:
		ResultClear_Draw();
		break;

	case SCENE_INDEX_RESULTOVER:
		ResultOver_Draw();
		break;
	}
}

void Scene_Check(void)
{
	if( g_SceneIndex != g_SceneNextIndex ) {
		Scene_Finalize();
		Scene_Initialize(g_SceneNextIndex);
	}
}

void Scene_Change(SCENE_INDEX index)
{
	g_SceneNextIndex = index;
}

