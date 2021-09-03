#pragma once
class YouDie : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	YouDie();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

