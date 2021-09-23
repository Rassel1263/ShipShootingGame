#pragma once
class FocusedFire : public ObjectUI
{
public:
	Sprite spr;
	RenderInfo ri;

	Sprite gauge;

	FocusedFire();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

