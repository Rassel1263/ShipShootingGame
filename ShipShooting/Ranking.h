#pragma once
class Ranking : public Object
{
public:
	Sprite bck;

	std::vector<RankInfo> rank;


	std::vector<Sprite> words[3];
	std::vector<Sprite> scores[3];

	std::wstring initial;
	std::vector<Sprite> font;
	std::vector<Sprite> curScore;

	RenderInfo ri;

	Ranking();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void ReadFile();
	void WriteFile();
};

