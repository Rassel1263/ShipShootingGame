#include "DXUT.h"
#include "AttackGuide.h"

AttackGuide::AttackGuide(D3DXVECTOR2 pos, D3DXVECTOR2 scale, float time, int index, std::function<void()> func)
{
	this->pos = pos;

	if (index == 1)
	{
		bck.LoadAll(L"Assets/Sprites/Obstacle/mineRange.png");
		bckRI.scale = scale;

		spr.LoadAll(L"Assets/Sprites/Obstacle/mineRange.png");
		ri.scale = D3DXVECTOR2(0.0f, 0.0f);
	}
	else if (index == 2)
	{
		bck.LoadAll(L"Assets/Sprites/guide2.png");
		bckRI.scale = scale;

		spr.LoadAll(L"Assets/Sprites/guide2.png");
		ri.scale = D3DXVECTOR2(1.0f, 0.0f);
	}

	this->func = func;
	this->time = time;
	this->index = index;
	this->maxTime = time;
}

void AttackGuide::Update(float deltaTime)
{
	time -= deltaTime;

	if(index == 1)
		ri.scale = bckRI.scale * (1 - time / maxTime);
	else if(index == 2)
		ri.scale.y = bckRI.scale.y * (1 - time / maxTime);

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
