#include "target.h"
#include "main.h"
#include "player.h"
#include "boss.h"
#include "sprite.h"
#include "nzoth.h"
#include "valkyr.h"

#define TARGET_MAX (10)

void Target_Draw(void)
{
	if (Player_GetTarget() != 0)
	{
		Sprite_Draw(TEXTURE_INDEX_SHADOW,
			1184.0f,
			96.0f,
			0,
			0,
			640,
			640,
			320,
			320,
			0.2f,
			0.2f,
			0.0f);
	}
	switch (Player_GetTarget())
	{
	case 0:
		break;
	case 1:
		Sprite_Draw(TEXTURE_INDEX_NZOTH,
			1184.0f,
			96.0f,
			0,
			0,
			32,
			32,
			16,
			16,
			2.5f,
			2.5f,
			0.0f);
		break;
	case 2:
		Sprite_Draw(TEXTURE_INDEX_NZOTH,
			1184.0f,
			96.0f,
			0,
			0,
			32,
			32,
			16,
			16,
			1.5f,
			1.5f,
			0.0f);
		break;
	case 3:
		Sprite_Draw(TEXTURE_INDEX_VALKYR,
			1184.0f,
			96.0f,
			0,
			0,
			32,
			32,
			16,
			16,
			2.5f,
			2.5f,
			3.1415f);
		break;
	default:
		break;
	} 
}

int Target_Search(int target)
{
	for (++target; target < TARGET_MAX; target++)
	{
		switch (target)
		{
		case 1:
			if (Boss_IsEnable())
				return target;
			break;
		case 2:
			if (Nzoth_GetIsEnable())
				return target;
			break;
		case 3:
			if (Valkyr_GetIsEnable())
				return target;
			break;
		default:
			break;
		}
	}

	return 1;
}

D3DXVECTOR2* Target_GetPospointer(int target)
{
	switch (target)
	{
	case 0:
		break;
	case 1:
		return Boss_GetPospointer();
		break;
	case 2:
		return Nzoth_GetPospointer();
		break;
	case 3:
		return Valkyr_GetPospointer();
		break;
	default:
		break;
	}
	return Boss_GetPospointer();
}

void Target_DrawHP(void)
{
	float target_hitpoint = 0;
	switch (Player_GetTarget())
	{
	case 0:
		break;
	case 1:
		target_hitpoint = Boss_GetHitPoint();
		target_hitpoint = target_hitpoint / BOSS_HITPOINT;
		break;
	case 2:
		target_hitpoint = Nzoth_GetHitPoint();
		target_hitpoint = target_hitpoint / NZOTH_HITPOINT;
		break;
	case 3:
		target_hitpoint = Valkyr_GetHitPoint();
		target_hitpoint = target_hitpoint / VALKYR_HITPOINT;
		break;
	default:
		break;
	}
	Sprite_Draw(TEXTURE_INDEX_HITPOINT,
		888.0f,
		64.0f,
		0,
		0,
		200 * target_hitpoint,
		20);
}