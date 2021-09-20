#pragma once

enum class EnemyType
{
	None,
	FloatingEnemy,
	FlyingEnemy,
};

class CEnemy : public Unit
{
public:
	EnemyType type = EnemyType::None;

	CEnemy(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli);
	virtual bool Move(float deltaTime) override;
	virtual void Destroy() {};
};

