#pragma once
#include "Unit.h"
#include "EnemyManager.h"

class MachineGun;
class Cannon;
class MissileTurret;
class CEnemy;

class Player : public Unit
{
public:
	MachineGun* machineGun = NULL;
	Cannon* cannon = NULL;
	CEnemy* Target = NULL;
	MissileTurret* turret = NULL;

	bool toggle = false;
	bool skill1 = false;

	float skil1Timer = 0.0f;
	float skill1CoolTime = 0.0f;

	Player();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) override;
	void SetTarget(EnemyType enemyType);
	void SetWeaponPos();
	void CameraControll();
	void ShootControll();
};

