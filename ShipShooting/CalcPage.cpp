#include "Header.h"
#include "CalcPage.h"
#include "Font.h"

CalcPage::CalcPage()
{
	Time::GetInstance().timeScale = 0.0f;

	spr.LoadAll(L"Assets/Sprites/UI/calc.png");
	spr.bCamera = false;

	layer = 15;

	this->hp = nowScene->player->ability.hp;
	this->time = nowScene->gameTime;
	this->totalScore = nowScene->score + nowScene->destScore;

	nowScene->obm.AddObject(new Font(L"Number/", hp, D3DXVECTOR2(-50, 150), D3DXVECTOR2(2, 2), 60, 0, layer + 1));
	nowScene->obm.AddObject(new Font(L"Number/", time, D3DXVECTOR2(-50, -70), D3DXVECTOR2(2, 2), 60, 0, layer + 1));
	nowScene->obm.AddObject(new Font(L"Number/", totalScore, D3DXVECTOR2(100, -400), D3DXVECTOR2(2, 2), 60, 0, layer + 1));

	stopTimer = 2.0f;
}

void CalcPage::Update(float deltaTime)
{
	stopTimer -= Time::GetInstance().unscaleTime;

	if (stopTimer > 0.0f) return;

	if (hp > 0)
		CalcNum(hp, Time::GetInstance().unscaleTime, 100);
	else if (time > 0)
		CalcNum(time, Time::GetInstance().unscaleTime, 100);
	else
	{
		if (Input::GetInstance().KeyDown(VK_RETURN))
		{
			Time::GetInstance().timeScale = 1.0f;
			Game::GetInstance().ChangeScene(nowScene->nextScene);
		}
	}
}

void CalcPage::Render()
{
	spr.Render(RenderInfo{});
}

void CalcPage::CalcNum(float& num, float deltaTime, float speed)
{
	float temp = num;

	num -= speed * deltaTime;

	if (num < 0)
		num = 0;

	totalScore += temp - num;
}
