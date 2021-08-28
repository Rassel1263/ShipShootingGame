#pragma once
#include "CWeapon.h"

class Cannon : public CWeapon
{
public:
	float rotate = 0.0f;

	Cannon(Unit* owner, D3DXVECTOR2 offset);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

