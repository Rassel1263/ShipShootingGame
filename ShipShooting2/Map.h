#pragma once
class Map : public Object
{
public:
	Sprite ocean;
	Sprite shadow;

	float cloudTimer = 0.0f;

	Map();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

