#include "Header.h"
#include "Ocean.h"

Ocean::Ocean()
{
	spr.LoadAll(L"Assets/Sprites/ocean.png");


	layer = -1;
}

void Ocean::Update(float deltaTime)
{
	pos.y -= deltaTime* nowScene->player->ability.speed;

	if (pos.y <= -1080)
		pos.y = 0;
}

void Ocean::Render()
{
	spr.Render(RenderInfo{ pos });
	spr.Render(RenderInfo{ D3DXVECTOR2(pos.x, pos.y + 1080) });
}
