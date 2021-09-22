#pragma once

struct RankInfo
{
	std::wstring initial = L"";
	std::wstring score = L"";
};

class WriteRank : public Object
{
public:
	Sprite bck;
	Sprite underBar;

	std::vector<RankInfo> ranks;
	std::vector<Sprite> curScore;
	std::vector<Sprite> curInitial;

	std::wstring initial = L"";
	std::wstring score = L"";

	std::vector<Sprite> prevInitial[3];
	std::vector<Sprite> prevScore[3];


	WriteRank();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void ReadFile();
	void WriteFile();
};

