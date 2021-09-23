#pragma once
class StageHelp : public ObjectUI
{
public:
	int index = 0;
	int count = 0;

	Sprite prevMap;
	Sprite curMap;
	Sprite complete;

	float stayTime = 1.0f;

	bool draw = true;

	RenderInfo ri;

	StageHelp(int index);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

