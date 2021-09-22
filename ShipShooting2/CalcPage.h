#pragma once
class CalcPage : public ObjectUI
{
public:
	Sprite bck;
	RenderInfo ri;

	Sprite fade;

	D3DXCOLOR fontColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	int index = 0;
	float drawFadeTimer = 0.0f;

	float stopTimer = 0.0f;

	float hp = 0.0f;
	float time = 0.0f;
	float kills = 0.0f;


	CalcPage();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void CalcNum(float& num, float deltaTime, float speed);
};

