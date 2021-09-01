#pragma once
#include "Unit.h"

enum class EnemyType
{
	None,
	FloatingEnemy,
	FlyingEnemy,
	BigShip,
	BigPlane,
};

class CEnemy : public Unit
{
public:
	EnemyType type = EnemyType::None;

	float attackTime = 0.0f;
	float attackTimer = 0.0f;

	ColorShader* colorShader = NULL;

	CEnemy();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) override;
	virtual void OnCollision(Collider& coli);
	virtual void Destroy();

	void CheckPos();

	void Hit(float damage);
};

