#include "Header.h"
#include "Effect.h"

Effect::Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float aniTime, float rotate, int index, D3DXVECTOR2 pivot, std::function<void()> func)
{
	spr.LoadAll(L"Assets/Sprites/Effect/" + eftName, aniTime, false);
	this->pos = pos;
	ri.scale = scale;
	this->visibleTime = aniTime;
	this->maxVisibleTime = aniTime;
	this->func = func;
	ri.rotate = rotate;

	ri.pivot = pivot;


	this->index = index;
}

void Effect::Update(float deltaTime)
{
	if (index == 1)
	{
		if (!spr.bAnimation)
		{
			destroy = true;
			if (func) func();
		}
	}

	if (index == 2)
	{
		visibleTime -= deltaTime;

		spr.color.a = visibleTime / maxVisibleTime;

		if (spr.color.a <= 0.0f)
			destroy = true;
	}

	spr.Update(deltaTime);
}

void Effect::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
