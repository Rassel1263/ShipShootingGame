#pragma once
class Ocean : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	Ocean();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

