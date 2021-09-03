#pragma once
class Help : public Object
{
public:
	Sprite spr;
	RenderInfo ri;

	Help();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

