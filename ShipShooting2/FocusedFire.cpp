#include "DXUT.h"
#include "FocusedFire.h"

FocusedFire::FocusedFire()
{
	spr.LoadAll(L"Assets/Sprites/ui/ingame/skills/focus/1.png");
	spr.bCamera = false;
	spr.color.a = 0.0f;

	gauge.LoadAll(L"Assets/Sprites/ui/ingame/skills/focus/g.png");
	gauge.color.a = 0.0f;
	gauge.bCamera = false;

	layer = -1;
}

void FocusedFire::Update(float deltaTime)
{
	if (nowScene->player->skill1)
	{
		if (spr.color.a <= 0.5f)
		{
			gauge.color.a += deltaTime;
			spr.color.a += deltaTime;
		}

		gauge.heightRatio = 1 - nowScene->player->skill1Timer / 5.0f;
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

	gauge.Render(RenderInfo{D3DXVECTOR2(200, 0)});
}
