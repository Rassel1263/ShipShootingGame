#pragma once
class Rank : public Object
{
public:
	Sprite bck;
	RenderInfo ri;

	std::vector<Sprite> initial[3];
	std::vector<Sprite> scores[3];

	std::vector<RankInfo> ranks;

	Rank();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

