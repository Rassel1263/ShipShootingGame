#pragma once
#include "WriteRank.h"

class Rank : public Object
{
public:
	Sprite bck;

	std::vector<RankInfo> ranks;

	std::vector<Sprite> initial[3];
	std::vector<Sprite> score[3];


	Rank();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void ReadFile();
};

