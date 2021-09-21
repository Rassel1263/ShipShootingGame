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
	float attackTime = 0.0f;
	float attackTimer = 0.0f;

	float turnSpeed = 0.0f;
	float turnTime = 0.0f;

	EnemyType type = EnemyType::None;

	CEnemy(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnCollision(Collider& coli) override;
	virtual void Hit(float damage) override;
	virtual void Attack(float deltaTime);
	virtual void Destroy();

	bool Move(float deltaTime) override;
};

