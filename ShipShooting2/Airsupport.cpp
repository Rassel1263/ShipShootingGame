#include "DXUT.h"
#include "Airsupport.h"

Airsupport::Airsupport(float x)
{
	//this->pos.x = pos.x;
	spr.LoadAll(L"Assets/Sprites/effect/AirSupport", 0.05f, false);
	spr.bCamera = false;
	SoundManager::GetInstance().Play(L"airMove");

	layer = -1;
}

void Airsupport::Update(float deltaTime)
{
	timer += deltaTime;
	if (timer < 2.0f) return;

	

	if (!spr.bAnimation)
		destroy = true;

	if ((spr.scene == 9 || spr.scene == 17 || spr.scene == 22) && !attack)
	{
		SoundManager::GetInstance().Play(L"airBoom");
		attack = true;
		Camera::GetInstance().cameraQuaken = { 15, 15 };
		for (auto& enemy : nowScene->enemyManager.allEnemys)
		{
			if (enemy->pos.x > Camera::GetInstance().cameraPos.x - 960 && enemy->pos.x < Camera::GetInstance().cameraPos.x + 960)
				enemy->Hit(60);
		}
	}
	else
		attack = false;
		

	spr.Update(deltaTime);
}

void Airsupport::Render()
{
	spr.Render(RenderInfo{pos});
}
