#pragma once
class FlyingEnemy : public CEnemy
{
public:
	FlyingEnemy(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli);
	virtual void Destroy() override;
};

