#pragma once
class BossIntro : public ObjectUI
{
public:
	Sprite spr;
	RenderInfo ri;

	float destColor = 1.0f;
	int blink = 0;

	BossIntro();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

