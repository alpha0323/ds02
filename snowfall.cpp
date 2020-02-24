#include "snowfall.h"
#include "sprite.h"
#include "texture.h"

SNOWFALL snowfall;

void Snowfall_Initialize() {
	snowfall.initialize();
}

void SNOWFALL::initialize() {
	//èâä˙âª
	for (int i = 0; i < SNOWFALL_MAX; i++)
	{
		snowfall.snow[i].pos.x = 0.0f;
		snowfall.snow[i].pos.y = SNOWFALL_START;
		snowfall.snow[i].velocity = 0.0f;
		snowfall.snow[i].velocityR = 0.0f;
		snowfall.snow[i].rotation = 0.0f;
		snowfall.snow[i].radius = 0.0f;

		snowfall.snow[i].enable = false;
	}

	snowfall.frame = 0;
}

void SNOWFALL::finalize() {

}

void SNOWFALL::update() {
	if (++snowfall.frame >= SNOWFALL_SKIP)
		snowfall.set();

	snowfall.move();
}

void SNOWFALL::draw() {
	//ç~ÇËÇÈê·àÛÇï`âÊÇ∑ÇÈ
	for (int i = 0; i < SNOWFALL_MAX; i++)
	{
		if (!snowfall.snow[i].enable)
			continue;

		Sprite_Draw(TEXTURE_INDEX_SNOWFALL,
			snowfall.snow[i].pos.x,
			snowfall.snow[i].pos.y,
			0,
			0,
			672,
			672,
			336,
			336,
			snowfall.snow[i].radius / 10,
			snowfall.snow[i].radius / 10,
			snowfall.snow[i].rotation);
	}
}

void SNOWFALL::set() {
	for (int i = 0; i < SNOWFALL_MAX; i++)
	{
		if (snowfall.snow[i].enable)
			continue;
		snowfall.snow[i].pos.x = rand() % 1200 + 40;
		snowfall.snow[i].pos.y = SNOWFALL_START;
		snowfall.snow[i].velocity = rand() % 10 + 1;
		snowfall.snow[i].velocityR = (rand() % 10) * 0.01;
		snowfall.snow[i].rotation = 0.0f;
		snowfall.snow[i].radius = (rand() % 11) * 0.1 + 0.4;
		snowfall.snow[i].enable = true;
		snowfall.frame = 0;
		break;
	}	
}

void SNOWFALL::move() {
	for (int i = 0; i < SNOWFALL_MAX; i++)
	{
		if (!snowfall.snow[i].enable)
			continue;
		if (snowfall.snow[i].pos.y >= SNOWFALL_OVER)
			snowfall.snow[i].enable = false;
		snowfall.snow[i].pos.y += snowfall.snow[i].velocity;
		snowfall.snow[i].rotation += snowfall.snow[i].velocityR;
	}
}