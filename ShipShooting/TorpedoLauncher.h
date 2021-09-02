#pragma once
#include "CWeapon.h"

class TorpedoLauncher : public CWeapon
{
public:
	TorpedoLauncher(Unit* owner);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Shoot() override;
};

