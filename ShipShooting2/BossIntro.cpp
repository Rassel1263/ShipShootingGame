#include "DXUT.h"
#include "BossIntro.h"

BossIntro::BossIntro()
{
	nowScene->player->fallowCamera = false;

	SoundManager::GetInstance().StopAll();
	SoundManager::GetInstance().Play(L"bossIntro");

	spr.LoadAll(L"Assets/Sprites/ui/ingame/bossIntro.png");
	spr.color.a = 0.0f;
	spr.bCamera = false;
	
}

void BossIntro::Update(float deltaTime)
{
	spr.color.a += deltaTime * destColor * 2;

	if (spr.color.a <= 0.0f || spr.color.a >= 1.0f)
	{
		spr.color.a = std::clamp(spr.color.a, 0.0f, 1.0f);
		blink++;
		destColor = -destColor;
	}

	if (blink >= 4)
	{
		SoundManager::GetInstance().Play(L"boss", true);
		destroy = true;
	}
}

void BossIntro::Render()
{
	spr.Render(RenderInfo{});
}
