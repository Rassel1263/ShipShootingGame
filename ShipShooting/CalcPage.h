#pragma once
class CalcPage : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	float hp = 0.0f;;
	float time = 0.0f;
	float totalScore = 0.0f;

	float stopTimer = 0.0f;

	CalcPage();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void CalcNum(float& num, float deltaTime, float speed);
};

