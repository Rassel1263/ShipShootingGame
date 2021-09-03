#include "Header.h"
#include "Ranking.h"

Ranking::Ranking()
{
	bck.LoadAll(L"Assets/Sprites/UI/Ranking.png");

	curScore.resize(6);

	WCHAR temp[10];
	wsprintf(temp, L"%06d", (int)nowScene->score);
	std::wstring str = temp;

	for (int i = 0; i < 6; ++i)
	{
		curScore[i].LoadAll(L"Assets/Sprites/UI/Font/Number/" + str.substr(i, 1) + L".png");
	}

	ReadFile();
}

void Ranking::Update(float deltaTime)
{
	if (initial.size() < 3)
	{
		for (char c = 'A'; c <= 'Z'; ++c)
		{
			if (Input::GetInstance().KeyDown(c))
			{
				initial += c;
				break;
			}
		}

		int size = initial.size();
		font.resize(size);

		for (int i = 0; i < size; ++i)
			font[i].LoadAll(L"Assets/Sprites/UI/Font/Word/" + initial.substr(i, 1) + L".png");
	}
	else
		WriteFile();

	if (!initial.empty())
	{
		if (Input::GetInstance().KeyDown(VK_BACK))
			initial.pop_back();
	}
}

void Ranking::Render()
{
	bck.Render(RenderInfo{});

	int xCnt = 0;
	for (auto& spr : curScore)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(-200 + xCnt * 70, 180), D3DXVECTOR2(2, 2)});
		xCnt++;
	}

	xCnt = 0;
	for (auto& spr : font)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(-400 + xCnt * 400, 20) });
		xCnt++;
	}

	int yCnt = 0;
	for (int i = 0; i < 3; ++i)
	{
		xCnt = 0;
		for (auto& spr : words[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(-150 + xCnt * 50, -225 - yCnt * 85), D3DXVECTOR2(0.4f, 0.4f)});
			xCnt++;
		}

		xCnt = 0;
		for (auto& spr : scores[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(200 + xCnt * 50, -225 - yCnt * 85) });
			xCnt++;
		}
		yCnt++;
	}
}

void Ranking::ReadFile()
{
	std::wifstream file(L"Assets/RankData.txt");

	rank.resize(3);

	if (file.is_open())
	{
		for (int i = 0; i < 3; ++i)
		{
			file >> rank[i].initial;
			file >> rank[i].score;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		words[i].resize(3);
		scores[i].resize(6);

		for (int j = 0; j < 3; ++j)
			words[i][j].LoadAll(L"Assets/Sprites/UI/Font/Word/" + rank[i].initial.substr(j, 1) + L".png");

		for (int j = 0; j < 6; ++j)
			scores[i][j].LoadAll(L"Assets/Sprites/UI/Font/Number/" + rank[i].score.substr(j, 1) + L".png");
	}
}

void Ranking::WriteFile()
{
	if (Input::GetInstance().KeyDown(VK_RETURN))
	{
		std::wofstream file(L"Assets/RankData.txt");

		RankInfo temp;
		temp.initial = initial;

		WCHAR str[10];

		wsprintf(str, L"%06d", (int)nowScene->score);
		temp.score = str;

		rank.push_back(temp);
		std::sort(rank.begin(), rank.end(), [](const RankInfo& lhs, const RankInfo& rhs) {return std::stoi(lhs.score) > std::stoi(rhs.score); });

		rank.erase(rank.end() - 1);

		for (int i = 0; i < 3; ++i)
		{
			file << rank[i].initial << std::endl;
			file << rank[i].score << std::endl;
		}

		Game::GetInstance().ChangeScene(new MainScene());
	}
}
