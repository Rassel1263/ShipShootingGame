#include "Header.h"
#include "TorpedoLauncher.h"
#include "Torpedo.h"

TorpedoLauncher::TorpedoLauncher(Unit* owner) : CWeapon(owner, D3DXVECTOR2(0, 0))
{
	shootInterval = 0.3f;
	bulletAmount = 15;
}

void TorpedoLauncher::Update(float deltaTime)
{
	CWeapon::Update(deltaTime);
}

void TorpedoLauncher::Render()
{
}

void TorpedoLauncher::Shoot()
{
	if (bulletAmount > 0)
	{
		if (shootTimer >= shootInterval)
		{
			bulletAmount--;
			shootTimer = 0;

			nowScene->obm.AddObject(new Torpedo(owner->pos, owner->target, damage));
		}
	}
	else
		SpawnUI();
}
