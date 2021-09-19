#pragma once
class Map : public Object
{
public:
	Sprite ocean;
	Sprite shadow;


	Map();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

