#include "DXUT.h"
#include "FocusedFire.h"

FocusedFire::FocusedFire()
{
	spr.LoadAll(L"Assets/Sprites//ui/ingame/skills/focus", 0.2f);
	spr.bCamera = false;
	spr.color.a = 0.0f;

	layer = -1;
}

void FocusedFire::Update(float deltaTime)
{
	if (nowScene->player->skill1)
	{
		if (spr.color.a <= 0.5f) spr.color.a += deltaTime;
	}
	else
	{
		spr.color.a -= deltaTime;

		if (spr.color.a <= 0.0f) destroy = true;
	}

	spr.Update(deltaTime);
}

void FocusedFire::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
