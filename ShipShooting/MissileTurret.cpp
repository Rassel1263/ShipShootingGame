#include "Header.h"
#include "MissileTurret.h"
#include "HomingBullet.h"

MissileTurret::MissileTurret(Unit* owner, D3DXVECTOR2 offset) : CWeapon(owner, offset)
{
	spr.LoadAll(L"Assets/Sprites/Unit/Player/Weapon/MissileTurret.png");

	shootInterval = 0.3f;
	bulletAmount = 10;
	damage = 15;
}

void MissileTurret::Update(float deltaTime)
{
	CWeapon::Update(deltaTime);
}

void MissileTurret::Render()
{
	CWeapon::Render();
}

void MissileTurret::Shoot()
{
	if (bulletAmount > 0)
	{
		if (shootTimer >= shootInterval)
		{
			shootTimer = 0;
			bulletAmount--;

			D3DXVECTOR2 fixedPos = pos + D3DXVECTOR2(-27, 12);
			nowScene->obm.AddObject(new Effect(L"CannonShot", fixedPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.0f), 0.05f, ri.rotate));
			nowScene->obm.AddObject(new HomingBullet(fixedPos, owner->target, damage, nowScene->GetRandomNumber(0, 360)));

			fixedPos = pos + D3DXVECTOR2(-19, 12);
			nowScene->obm.AddObject(new Effect(L"CannonShot", fixedPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.0f), 0.05f, ri.rotate));
			nowScene->obm.AddObject(new HomingBullet(fixedPos, owner->target, damage, nowScene->GetRandomNumber(0, 360)));

			fixedPos = pos + D3DXVECTOR2(19, 12);
			nowScene->obm.AddObject(new Effect(L"CannonShot", fixedPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.0f), 0.05f, ri.rotate));
			nowScene->obm.AddObject(new HomingBullet(fixedPos, owner->target, damage, nowScene->GetRandomNumber(0, 360)));

			fixedPos = pos + D3DXVECTOR2(27, 12);
			nowScene->obm.AddObject(new Effect(L"CannonShot", fixedPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.0f), 0.05f, ri.rotate));
			nowScene->obm.AddObject(new HomingBullet(fixedPos, owner->target, damage, nowScene->GetRandomNumber(0, 360)));
		}
	}
	else
		SpawnUI();
}
