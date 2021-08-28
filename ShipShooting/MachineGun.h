#pragma once
#include "CWeapon.h"

class MachineGun : public CWeapon
{
public:
	MachineGun(Unit* owner, D3DXVECTOR2 offset);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Shoot() override;
};

