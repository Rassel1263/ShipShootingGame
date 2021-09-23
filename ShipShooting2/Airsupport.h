#pragma once
class Airsupport : public ObjectUI
{
public:
	Sprite spr;

	float timer = 0.0f;
	bool attack = false;

	Airsupport(float x);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

