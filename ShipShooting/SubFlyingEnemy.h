#pragma once
class SubFlyingEnemy : public FlyingEnemy
{
public:
	float angle = 0.0f;
	float addAngle = 0.0f;
	float maxAngle = 0.0f;
	float speed = 0.0f;

	SubFlyingEnemy(D3DXVECTOR2 pos, float startAngle, float addAngle, float maxAngle, float speed);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Destroy() override;
};

