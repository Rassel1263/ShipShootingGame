#include "DXUT.h"
#include "CWeapon.h"

CWeapon::CWeapon(Unit* owner)
{
	this->owner = owner;
}

void CWeapon::Update(float deltaTime)
{
	if (shootTimer < shootInterval)
	{
		shootTimer += deltaTime;

		if (shootTimer >= shootInterval)
			shootTimer = shootInterval;
	}
}

////////////////////////////////////
/// MachineGun
////////////////////////////////////

MachineGun::MachineGun(Unit* owner) : CWeapon(owner)
{
	bulletAmount = 150;
	bulletMaxAmount = 30;
	shootInterval = 0.15f;

	reloadTime = 5.0f;

	damage = 5;
}

void MachineGun::Update(float deltaTime)
{
	if (reload)
	{
		reloadTimer += deltaTime;
		if (reloadTimer >= reloadTime)
		{
			bulletAmount += bulletMaxAmount;
			reload = false;
			reloadTimer = 0.0f;
			nowScene->msgBox->SpawnMsgBox(L"machinegunReady");
		}
	}

	CWeapon::Update(deltaTime);
}

void MachineGun::Shoot()
{
	if (bulletAmount > 0 && !reload)
	{
		if (shootTimer >= shootInterval)
		{
			shootTimer = 0.0f;

			if(!nowScene->player->skill1)
				bulletAmount--;

			nowScene->obm.AddObject(new Effect(L"shoot_machinegun/", owner->pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), 1, true, 0.05f));
			nowScene->obm.AddObject(new MachinegunBullet(owner->pos, owner->target, L"ally", 10));
		}
	}
	else
		reload = true;
}

////////////////////////////////////
/// NavalGun
////////////////////////////////////

NavalGun::NavalGun(Unit* owner) : CWeapon(owner)
{
	bulletAmount = 5;
	bulletMaxAmount = 5;
	shootInterval = 0.5f;

	reloadTime = 1.0f;
	reloadTimer = 0.0f;

	damage = 5;
}

void NavalGun::Update(float deltaTime)
{
	if (bulletAmount < 5)
	{
		reloadTimer += deltaTime;
		if (reloadTimer >= reloadTime)
		{
			bulletAmount++;
			reloadTimer = 0.0f;

			if (bulletAmount == bulletMaxAmount)
				nowScene->msgBox->SpawnMsgBox(L"navagunReady");
		}
	}

	CWeapon::Update(deltaTime);
}

void NavalGun::Shoot()
{
	if (bulletAmount > 0)
	{
		if (shootTimer >= shootInterval)
		{
			Camera::GetInstance().cameraQuaken = { 5, 5 };
			shootTimer = 0.0f;
			bulletAmount--;

			if (owner->target)
			{
				owner->target->Hit(damage);

				nowScene->obm.AddObject(new Effect(L"shoot_navalgun/", owner->pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), 1, true, 0.05f));
				nowScene->obm.AddObject(new Effect(L"Hit_navalgun/", owner->target->pos + nowScene->GetRandomVector(-50, 50, -50, 50), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), 1, true, 0.03f, -nowScene->GetAngleFromTarget(owner->pos, owner->target->pos) + 90));
			}
			else
				nowScene->obm.AddObject(new Effect(L"Hit_navalgun/", owner->pos + nowScene->GetRandomVector(-800, 800, 500, 800), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.03f));
		}
	}
}

////////////////////////////////////
/// Torpedo
////////////////////////////////////

TorpedoLauncher::TorpedoLauncher(Unit* owner) : CWeapon(owner)
{
	shootInterval = 0.3f;
	bulletMaxAmount = 15;
	bulletAmount = 15;
	damage = 10;
}

void TorpedoLauncher::Shoot()
{
	if (bulletAmount > 0)
	{
		if (shootTimer >= shootInterval)
		{
			bulletAmount--;
			shootTimer = 0.0f;

			nowScene->obm.AddObject(new HomingBullet(owner->pos, owner->target, CBullet::BulletType::Torpedo, L"ally", damage,
				owner->curRotate, 0.2f));
		}
	}
}

////////////////////////////////////
/// Missile
////////////////////////////////////

MissileTurret::MissileTurret(Unit* owner) : CWeapon(owner)
{
	shootInterval = 0.3f;
	bulletMaxAmount = 10;
	bulletAmount = 10;
	damage = 15;
}

void MissileTurret::Shoot()
{
	if (bulletAmount > 0)
	{
		if (shootTimer >= shootInterval)
		{
			bulletAmount--;
			shootTimer = 0.0f;

			nowScene->obm.AddObject(new Effect(L"shoot_missile/", owner->pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.0f), 1, true, 0.05f));

			nowScene->obm.AddObject(new HomingBullet(owner->pos, owner->target, CBullet::BulletType::Missile, L"ally", damage,
				owner->curRotate, 0.2f));
		}
	}
}
