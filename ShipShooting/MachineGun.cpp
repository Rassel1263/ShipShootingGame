#include "Header.h"
#include "MachineGun.h"
#include "MachinegunBullet.h"

MachineGun::MachineGun(Unit* owner, D3DXVECTOR2 offset) : CWeapon(owner, offset)
{
	spr.LoadAll(L"Assets/Sprites/Unit/Player/Weapon/MachineGun.png");

	bulletAmount = 30;
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
		}
	}

	CWeapon::Update(deltaTime);
}

void MachineGun::Render()
{
	CWeapon::Render();
}

void MachineGun::Shoot()
{
	if (bulletAmount > 0 && !reload)
	{

		if (shootTimer >= shootInterval)
		{
			shootTimer = 0.0f;
			if (!nowScene->player->skill1)
				bulletAmount -= 2;

			nowScene->obm.AddObject(new MachinegunBullet(D3DXVECTOR2(pos.x - 5, pos.y), owner->target, damage));
			nowScene->obm.AddObject(new MachinegunBullet(D3DXVECTOR2(pos.x + 5, pos.y), owner->target, damage));

			SoundManager::GetInstance().Play(L"Assets/Sound/Machine.mp3", false);
		}
	}
	else
	{
		reload = true;
		SpawnUI();
	}

}
