#pragma once
class SubFlyingEnemy : public FlyingEnemy
{
public:
	float angle = 0.0f;

	SubFlyingEnemy(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Destroy() override;
};

