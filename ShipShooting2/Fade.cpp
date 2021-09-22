#include "DXUT.h"
#include "Fade.h"

Fade::Fade(std::function<void()> func)
{
	spr.LoadAll(L"Assets/Sprites/black.png");
	spr.bCamera = false;
	spr.color.a = 0.0f;

	this->func = func;

	layer = 4;
}

void Fade::Update(float deltaTime)
{
	spr.color.a += deltaTime;

	if (spr.color.a > 1.0f)
	{
		if (func)
			func();
	}
}

void Fade::Render()
{
	spr.Render(RenderInfo{});
}
