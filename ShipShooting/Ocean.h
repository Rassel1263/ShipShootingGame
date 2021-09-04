#pragma once
class Ocean : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	float speed = 0.0f;

	Ocean();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

