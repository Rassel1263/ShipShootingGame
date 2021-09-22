#pragma once
class StageHelp : public ObjectUI
{
public:
	Sprite prevMap;
	Sprite curMap;

	float stayTime = 1.0f;

	bool draw = true;

	RenderInfo ri;

	StageHelp();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

