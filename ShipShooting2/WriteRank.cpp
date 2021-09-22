#include "DXUT.h"
#include "WriteRank.h"

WriteRank::WriteRank()
{
	bck.LoadAll(L"Assets/Sprites/black.png");
	underBar.LoadAll(L"Assets/Sprites/ui/Font/apb/underbar.png");

	WCHAR temp[256] = L"";
	wsprintf(temp, L"%06d", (int)nowScene->score);
	score = temp;

	int size = score.size();

	curScore.resize(size);

	for (int i = 0; i < size; ++i)
		curScore[i].LoadAll(L"Assets/Sprites/ui/Font/Number/" + score.substr(i, 1) + L".png");

	ReadFile();
}

void WriteRank::Update(float deltaTime)
{
	if (initial.size() < 3)
	{
		for (char c = 'A'; c < 'Z'; ++c)
		{
			if (Input::GetInstance().KeyDown(c))
			{
				initial.push_back(c);
				break;
			}
		}


		int size = initial.size();
		curInitial.resize(size);

		for (int i = 0; i < size; ++i)
			curInitial[i].LoadAll(L"Assets/Sprites/ui/Font/apb/" + initial.substr(i, 1) + L".png");
	}
	else
	{
		if (Input::GetInstance().KeyDown(VK_RETURN))
			WriteFile();
	}

	if (!initial.empty())
	{
		if (Input::GetInstance().KeyDown(VK_BACK))
			initial.pop_back();
	}
}

void WriteRank::Render()
{
	bck.Render(RenderInfo{});

	int xCnt = 0;
	for (auto& spr : curScore)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(-200 + xCnt * 80, 200), D3DXVECTOR2(1.5, 1.5) });
		xCnt++;
	}

	xCnt = 0;
	for (auto& spr : curInitial)
	{
		spr.Render(RenderInfo{ D3DXVECTOR2(-400 + xCnt * 400, 0), D3DXVECTOR2(1.5, 1.5) });
		underBar.Render(RenderInfo{ D3DXVECTOR2(-400 + xCnt * 400, -60), D3DXVECTOR2(1.5, 1.5) });
		xCnt++;
	}

	for (int i = 0; i < 3; ++i)
	{
		xCnt = 0;
		for (auto& spr : prevInitial[i])
		{
			spr.Render(RenderInfo{D3DXVECTOR2(-200 + xCnt * 50, -200 - i *100), D3DXVECTOR2(0.5, 0.5)});
			xCnt++;
		}

		for (auto& spr : prevScore[i])
		{
			spr.Render(RenderInfo{ D3DXVECTOR2(-100 + xCnt * 50, -200 - i * 100), D3DXVECTOR2(0.7, 0.7) });
			xCnt++;
		}
	}
}

void WriteRank::ReadFile()
{

	std::wifstream file(L"Assets/RankData.txt");

	ranks.resize(3);

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
		prevInitial[i].resize(3);
		prevScore[i].resize(6);

		for (int j = 0; j < 6; ++j)
		{
			if (j < 3)
				prevInitial[i][j].LoadAll(L"Assets/Sprites/ui/Font/apb/" + ranks[i].initial.substr(j, 1) + L".png");

			prevScore[i][j].LoadAll(L"Assets/Sprites/ui/Font/Number/" + ranks[i].score.substr(j, 1) + L".png");
		}
	}
}

void WriteRank::WriteFile()
{
	std::wofstream file(L"Assets/RankData.txt");

	RankInfo temp;
	temp.initial = initial;
	temp.score = score;

	ranks.push_back(temp);
	std::sort(ranks.begin(), ranks.end(), [](const RankInfo& lhs, const RankInfo& rhs) {return std::stoi(lhs.score) > std::stoi(rhs.score); });

	ranks.erase(ranks.end() - 1);

	for (int i = 0; i < 3; ++i)
	{
		file << ranks[i].initial << std::endl;
		file << ranks[i].score << std::endl;
	}

	Game::GetInstance().ChangeScene(new MainScene());
}
