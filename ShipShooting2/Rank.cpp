#include "DXUT.h"
#include "Rank.h"

Rank::Rank()
{
	bck.LoadAll(L"Assets/Sprites/ui/outgame/rank/a.png");
	bck.color.a = 0.0f;

	ReadFile();
}

void Rank::Update(float deltaTime)
{
	if (static_cast<MainScene*>(nowScene)->input)
	{
		if (bck.color.a < 1.0f)
			bck.color.a += deltaTime;
	}
	else
	{
		bck.color.a -= deltaTime;
		if (bck.color.a <= 0.0f)
			destroy = true;
	}

	if (bck.color.a >= 1.0f)
	{
		if (Input::GetInstance().KeyDown(VK_RETURN))
			static_cast<MainScene*>(nowScene)->input = false;
	}
}

void Rank::Render()
{
	bck.Render(RenderInfo{});

	for (int i = 0; i < 3; ++i)
	{
		int xCnt = 0;
		for (auto& spr : initial[i])
		{
			spr.color.a = bck.color.a;
			spr.Render(RenderInfo{ D3DXVECTOR2(-240 + xCnt * 100, 150 - i * 200) });
			xCnt++;
		}

		xCnt = 0;

		for (auto& spr : score[i])
		{
			spr.color.a = bck.color.a;
			spr.Render(RenderInfo{ D3DXVECTOR2(380 + xCnt * 70, 150 - i * 200), D3DXVECTOR2(2, 2)});
			xCnt++;
		}
	}

}

void Rank::ReadFile()
{
	ranks.resize(3);
	std::wifstream file(L"Assets/RankData.txt");

	if (file.is_open())
	{
		for (int i = 0; i < 3; ++i)
		{
			file >> ranks[i].initial;
			file >> ranks[i].score;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		initial[i].resize(3);
		score[i].resize(6);

		for (int j = 0; j < 6; ++j)
		{
			if (j < 3)
				initial[i][j].LoadAll(L"Assets/Sprites/ui/Font/apb/" + ranks[i].initial.substr(j, 1) + L".png");

			score[i][j].LoadAll(L"Assets/Sprites/ui/Font/Number/" + ranks[i].score.substr(j, 1) + L".png");
		}
	}
}
