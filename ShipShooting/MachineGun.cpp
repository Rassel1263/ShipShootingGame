#include "Header.h"
#include "MachineGun.h"
#include "MachinegunBullet.h"

MachineGun::MachineGun(Unit* owner, D3DXVECTOR2 offset) : CWeapon(owner, offset)
{
	spr.LoadAll(L"Assets/Sprites/Unit/Player/Weapon/MachineGun.png");

	bulletAmount = 30;
	bulletMaxAmount = 30;
	shootInterval = 0.05f;

	reloadTime = 5.0f;
}

void MachineGun::Update(float deltaTime)
{
	if (bulletAmount <= 0)
	{
		reloadTimer += deltaTime;

		if (reloadTimer >= reloadTime)
		{
			bulletAmount = bulletMaxAmount;
			reloadTimer = 0.0f;
		}
	}

	shootInterval -= deltaTime;
	CWeapon::Update(deltaTime);
}

void MachineGun::Render()
{
	CWeapon::Render();
}

void MachineGun::Shoot()
{
	if (bulletAmount > 0)
	{
		if (shootInterval <= 0.0f)
		{
			shootInterval = 0.05f;
			bulletAmount -= 2;
			nowScene->obm.AddObject(new MachinegunBullet(D3DXVECTOR2(pos.x - 5, pos.y)));
			nowScene->obm.AddObject(new MachinegunBullet(D3DXVECTOR2(pos.x + 5, pos.y)));
		}
	}

}
