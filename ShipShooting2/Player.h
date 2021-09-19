#pragma once
class Player : public Unit
{
public:
	Sprite spr;
	RenderInfo ri;

	float forwardAngle = 0.0f;

	int speedLevel = 0;

	Player();
	
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) override;

	void CameraControll();
};

