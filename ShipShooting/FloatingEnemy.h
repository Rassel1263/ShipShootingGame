#pragma once
#include "CEnemy.h"

class FloatingEnemy : public CEnemy
{
public:
	float attackTime = 0.0f;
	float attackTimer = 0.0f;

	FloatingEnemy(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Destroy() override;

};

