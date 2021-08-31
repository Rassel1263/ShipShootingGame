#include "Header.h"
#include "Effect.h"

Effect::Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, float aniTime, float rotate,std::function<void()> func)
{
	spr.LoadAll(L"Assets/Sprites/Effect/" + eftName, aniTime, false);
	this->pos = pos;
	ri.scale = scale;
	this->visibleTime = aniTime;
	this->maxVisibleTime = aniTime;
	this->func = func;
	ri.rotate = rotate;
	ri.pivot = pivot;

	this->index = 1;
}

Effect::Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float aniTime, float visibleTime, float rotate, std::function<void()> func)
{
	spr.LoadAll(L"Assets/Sprites/Effect/" + eftName, aniTime, false);
	this->pos = pos;
	ri.scale = scale;
	this->visibleTime = visibleTime;
	this->maxVisibleTime = visibleTime;
	this->func = func;
	ri.rotate = rotate;

	this->index = 2;
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
		{
			if (func) func();
			destroy = true;
		}
	}

	spr.Update(deltaTime);
}

void Effect::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
