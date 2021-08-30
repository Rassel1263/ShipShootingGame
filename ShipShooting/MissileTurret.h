#pragma once
#include "CWeapon.h"

class MissileTurret : public CWeapon
{
public:
	MissileTurret(Unit* owner, D3DXVECTOR2 offset);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Shoot() override;
};

