#include "DXUT.h"
#include "AttackGuide.h"

AttackGuide::AttackGuide(D3DXVECTOR2 pos, D3DXVECTOR2 scale, float time, std::function<void()> func)
{
	this->pos = pos;

	bck.LoadAll(L"Assets/Sprites/Obstacle/mineRange.png");
	bckRI.scale = scale;

	spr.LoadAll(L"Assets/Sprites/Obstacle/mineRange.png");
	ri.scale = D3DXVECTOR2(0.0f, 0.0f);

	this->time = time;
	this->maxTime = time;
}

void AttackGuide::Update(float deltaTime)
{
	time -= deltaTime;
	ri.scale = bckRI.scale * (1 - time / maxTime);

	if (time <= 0.0f)
	{
		if (func)
			func();

		destroy = true;
	}
}

void AttackGuide::Render()
{
	ri.pos = bckRI.pos = pos;

	bck.Render(bckRI);
	spr.Render(ri);
}
