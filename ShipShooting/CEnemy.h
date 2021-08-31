#pragma once
#include "Unit.h"

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

	CEnemy();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) override;
	virtual void OnCollision(Collider& coli);
	virtual void Destroy();

	void Hit(float damage);
};

