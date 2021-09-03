#pragma once
class BossIntro : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	bool& bossIntro;
	float destColor = 1.0f;
	bool reverseAlpha = false;

	BossIntro(bool& intro);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

