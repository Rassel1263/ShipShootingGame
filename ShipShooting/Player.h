#pragma once
#include "Unit.h"
#include "EnemyManager.h"

class MachineGun;
class Cannon;
class MissileTurret;
class TorpedoLauncher;
class CEnemy;

class Player : public Unit
{
public:
	MachineGun* machineGun = NULL;
	Cannon* cannon = NULL;
	CEnemy* Target = NULL;
	MissileTurret* turret = NULL;
	TorpedoLauncher* torpedLauncher = NULL;

	bool zoom = false;
	bool stop = false;
	bool skill1 = false;
	bool skill2 = false;
	bool speedUp = false;
	bool speedDown = false;
	bool invincible = false;
	bool god = false;

	float skill1Timer = 0.0f;
	float skill1CoolTime = 0.0f;
	float skill2CoolTime = 10.0f;

	float speedUpTime = 0.0f;
	float prevSpeed = 0.0f;
	float minSpeed = 0.0f;
	float invincibleTime = 0.0f;

	float speedDownTime = 0.0f;

	float uiTime = 0.0f;

	Player();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual bool Move(float deltaTime) override;
	virtual void Hit(float damage) override;
	virtual void OnCollision(Collider& coli) override;
	void SetTarget(EnemyType enemyType);
	void SetWeaponPos();
	void CameraControll();
	void ShootControll();
	void FirstSkillControll(float deltaTime);
	void SecondSkillControll(float deltaTime);
	void UpdateEffect(float deltaTime);
	void GetItemEffective(int index);
	void SpawnUI();
};

