#pragma once
#include "Unit.h"

class MachineGun;
class Cannon;
class Player : public Unit
{
public:
	MachineGun* machineGun = NULL;
	Cannon* cannon = NULL;

	Player();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) override;
	void SetWeaponPos();
};

