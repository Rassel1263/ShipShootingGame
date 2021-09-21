#pragma once
class FocusedFire : public ObjectUI
{
public:
	Sprite spr;
	RenderInfo ri;

	FocusedFire();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

