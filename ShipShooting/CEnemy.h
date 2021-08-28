#pragma once
#include "Unit.h"

class CEnemy : public Unit
{
public:
	CEnemy();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) override;
};

