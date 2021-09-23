#include "DXUT.h"
#include "CalcPage.h"

CalcPage::CalcPage()
{
	bck.LoadAll(L"Assets/Sprites/message/stageResult/stageresult.png");
	bck.color.a = 0.0f;
	bck.bCamera = false;

	fade.LoadAll(L"Assets/Sprites/black.png");
	fade.color.a = 0.0f;
	fade.bCamera = false;

	this->hp = nowScene->player->ability.hp;
	this->time = nowScene->gameTime;
	this->kills = nowScene->player->kills;
	nowScene->score = nowScene->score + nowScene->destScore;
	nowScene->destScore = 0.0f;

	fontColor.a = 0.0f;

	layer = 3;

	nowScene->obm.AddObject(new Font(L"a", hp, D3DXVECTOR2(0, 280), D3DXVECTOR2(1, 1), 100, 0, layer + 1, &fontColor));
	nowScene->obm.AddObject(new Font(L"a", time, D3DXVECTOR2(0, 80), D3DXVECTOR2(1, 1), 100, 0, layer + 1, &fontColor));
	nowScene->obm.AddObject(new Font(L"a", kills, D3DXVECTOR2(0, -140), D3DXVECTOR2(1, 1), 100, 0, layer + 1, &fontColor));
	nowScene->obm.AddObject(new Font(L"a", nowScene->score, D3DXVECTOR2(0, -350), D3DXVECTOR2(1, 1), 100, 0, layer + 1, &fontColor));
}

void CalcPage::Update(float deltaTime)
{
	if (index == 0)
	{
		if (bck.color.a < 1.0f)
		{
			bck.color.a += deltaTime;
			fontColor.a = bck.color.a;
		}
		else
		{
			stopTimer += deltaTime;

			if (stopTimer >= 1.0f)
			{
				if (hp > 0)
					CalcNum(hp, deltaTime, 100);
				else if (time > 0)
					CalcNum(time, deltaTime, 100);
				else if (kills > 0)
					CalcNum(kills, deltaTime, 100);
				else
				{
					if (Input::GetInstance().KeyDown(VK_RETURN))
						index++;
				}
			}
		}
	}
	else if (index == 1)
	{
		if (nowScene->curStage == 1)
		{
			auto lambda = [] {Game::GetInstance().ChangeScene(nowScene->nextScene);  };
			nowScene->obm.AddObject(new Fade(lambda));
			index++;
		}
		else
		{
			bck.color.a -= deltaTime;
			fontColor.a -= deltaTime;

			if (bck.color.a <= 0.0f)
			{
				nowScene->obm.AddObject(new StageHelp(3));
				index++;
				destroy = true;
			}
		}

	}

}

void CalcPage::Render()
{
	bck.Render(RenderInfo{});
	fade.Render(RenderInfo{});
}

void CalcPage::CalcNum(float& num, float deltaTime, float speed)
{
	float tempNum = num;

	num -= speed * deltaTime;

	if (num < 0) num = 0;

	nowScene->score += tempNum - num;
}
