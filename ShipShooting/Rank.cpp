#include "Header.h"
#include "Rank.h"

Rank::Rank()
{
	bck.LoadAll(L"Assets/Sprites/UI/Rank.png");

	bck.color.a = 0.0f;

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
		scores[i].resize(6);

		for (int j = 0; j < 3; ++j)
		{
			initial[i][j].LoadAll(L"Assets/Sprites/UI/Font/Word/" + ranks[i].initial.substr(j, 1) + L".png");
			initial[i][j].color.a = 0.0f;
		}

		for (int j = 0; j < 6; ++j)
		{
			scores[i][j].LoadAll(L"Assets/Sprites/UI/Font/Number/" + ranks[i].score.substr(j, 1) + L".png");
			scores[i][j].color.a = 0.0f;
		}
	}
}

void Rank::Update(float deltaTime)
{
	if (!static_cast<MainScene*>(nowScene)->input)
	{
		if (bck.color.a < 1.0f) bck.color.a += deltaTime;
	}
	else
	{
		bck.color.a -= deltaTime;
		if (bck.color.a <= 0.0f)
			destroy = true;
	}

	if (bck.color >= 1.0f)
	{
		if (Input::GetInstance().KeyDown(VK_RETURN))
			static_cast<MainScene*>(nowScene)->input = true;

	}
}

void Rank::Render()
{
	ri.pos = pos;
	bck.Render(ri);

	int yCnt = 0;
	for (int i = 0; i < 3; ++i)
	{
		int xCnt = 0;
		for (auto& spr : initial[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(-300 + xCnt * 100, 100 - yCnt * 200), D3DXVECTOR2(0.9, 0.9)});
			xCnt++;

			spr.color.a = bck.color.a;
		}

		xCnt = 0;
		for (auto& spr : scores[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(100 + xCnt * 100, 100 - yCnt * 200), D3DXVECTOR2(3, 3)});
			xCnt++;

			spr.color.a = bck.color.a;
		}

		yCnt++;
	}
}
