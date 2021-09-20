#pragma once

class Unit;
class CWeapon
{
public:

	int bulletAmount = 0;
	int bulletMaxAmount = 0;

	float shootInterval = 0.0f;
	float shootTimer = 0.0f;

	float damage = 0.0f;

	Unit* owner = NULL;

	CWeapon(Unit* owner);

	virtual void Update(float deltaTime);
	virtual void Shoot() = 0;
};

class MachineGun : public CWeapon
{
public:
	bool reload = false;

	float reloadTime = 0.0f;
	float reloadTimer = 0.0f;

	MachineGun(Unit* owner);

	virtual void Update(float deltaTime) override;
	virtual void Shoot() override;
};

class NavalGun : public CWeapon
{
public:
	float reloadTime = 0.0f;
	float reloadTimer = 0.0f;

	NavalGun(Unit* owner);

	virtual void Update(float deltaTime) override;
	virtual void Shoot() override;
};

class TorpedoLauncher : public CWeapon
{
public:
	TorpedoLauncher(Unit* owner);

	virtual void Shoot() override;
};

class MissileTurret : public CWeapon
{
public:
	MissileTurret(Unit* owner);

	virtual void Shoot() override;
};


