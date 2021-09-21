#include "DXUT.h"
#include "Effect.h"

Effect::Effect(std::wstring eftName, D3DXVECTOR2 pos, D3DXVECTOR2 scale, D3DXVECTOR2 pivot, int index, bool bCamera, float aniTime, float rotate, std::function<void()> func)
{
	std::wstring filePath = L"Assets/Sprites/effect/" + eftName;

	this->pos = pos;
	ri.scale = scale;
	ri.pivot = pivot;
	spr.bCamera = bCamera;

	this->index = index;
	
	spr.LoadAll(filePath, 0.05f, false);
	ri.rotate = rotate;

	if (index == 1)
		spr.aniMaxTime = aniTime;
	else if (index == 2)
	{
		visibleTime = aniTime;
		maxVisibleTime = visibleTime;
	}

	this->func = func;

	layer = 10;
}

void Effect::Update(float deltaTime)
{
	if (index == 1)
	{
		if (!spr.bAnimation)
		{
			if (func) func();

			destroy = true;
		}
	}
	else if (index == 2)
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
