#include "Header.h"
#include "BossIntro.h"

BossIntro::BossIntro(bool& intro) : bossIntro(intro)
{
	spr.LoadAll(L"Assets/Sprites/UI/bossIntro.png");
	spr.bCamera = false;
	spr.color.a = 0.0f;

	layer = 10;
}

void BossIntro::Update(float deltaTime)
{
	if (!bossIntro)
		if (spr.color.a <= 0.0f)
			destroy = true;

	if (spr.color.a <= 0.0f || spr.color.a >= 1.0f)
		destColor = -destColor;

	spr.color.a += deltaTime * destColor;
	spr.color.a = std::clamp(spr.color.a, 0.0f, 1.0f);

}

void BossIntro::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
