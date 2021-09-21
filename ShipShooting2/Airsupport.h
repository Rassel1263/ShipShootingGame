#pragma once
class Airsupport : public Object
{
public:
	Sprite spr;

	bool attack = false;

	Airsupport(float x);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

