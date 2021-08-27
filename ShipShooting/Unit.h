#pragma once

class Unit : public Object
{
public:
	Sprite spr;
	Unit();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

