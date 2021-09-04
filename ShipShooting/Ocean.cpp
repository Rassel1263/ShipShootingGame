#include "Header.h"
#include "Ocean.h"

Ocean::Ocean()
{
	spr.LoadAll(L"Assets/Sprites/ocean" + std::to_wstring(nowScene->curStage) + L".png");

	speed = 300;
	layer = -10;
}

void Ocean::Update(float deltaTime)
{
	if(!nowScene->spawnBoss)
		pos.y -= deltaTime* nowScene->player->ability.speed;
	else
	{
		pos.y -= deltaTime * speed;

		if(speed > 0.0f)
			speed -= deltaTime * 70;
	}

	if (pos.y <= -1080)
		pos.y = 0;
}

void Ocean::Render()
{
	spr.Render(RenderInfo{ pos });
	spr.Render(RenderInfo{ D3DXVECTOR2(pos.x, pos.y + 1080) });
}
