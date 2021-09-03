#pragma once

struct RankInfo
{
	std::wstring initial = L"";
	std::wstring score = L"";
};

class RankingScene : public Scene
{
public:
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

