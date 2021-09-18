#include "Header.h"
#include "Cannon.h"

Cannon::Cannon(Unit* owner, D3DXVECTOR2 offset) : CWeapon(owner, offset)
{
	spr.LoadAll(L"Assets/Sprites/Unit/Player/Weapon/Cannon.png");
	ri.pivot = { 0.5, 0.2 };

	bulletAmount = 5;
	bulletMaxAmount = 5;
	shootInterval = 0.5f;

	reloadTime = 1.0f;
}

void Cannon::Update(float deltaTime)
{
	if (owner->target != NULL)
	{
		D3DXVECTOR2 distance = owner->target->pos - pos;
		D3DXVec2Normalize(&distance, &distance);
		float angle = atan2(distance.y, distance.x);

		ri.rotate = D3DXToDegree(-angle) + 90;
	}
	else
		ri.rotate = 0;

	if (bulletAmount < 5)
	{
		reloadTimer += deltaTime;
		if (reloadTimer >= reloadTime)
		{
			bulletAmount++;
			reloadTimer = 0.0f;
		}
	}

	CWeapon::Update(deltaTime);
}

void Cannon::Render()
{
	CWeapon::Render();
}

void Cannon::Shoot()
{
	if (bulletAmount > 0)
	{
		if (shootTimer >= shootInterval)
		{
			Camera::GetInstance().cameraQuaken = { 5, 5 };

			shootTimer = 0.0f;
			bulletAmount--;
			float radian = D3DXToRadian(-ri.rotate + 80);
			D3DXVECTOR2 fixpos = pos + D3DXVECTOR2(cosf(radian), sinf(radian)) * 13;
			D3DXVECTOR2 targetPos = (owner->target) ? owner->target->pos : D3DXVECTOR2(nowScene->GetRandomNumber(-200, 200), (100, 200));
			if (owner->target) owner->target->Hit(5);

			nowScene->obm.AddObject(new Effect(L"CannonShot", fixpos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.0f), 0.05f, ri.rotate));
			nowScene->obm.AddObject(new Effect(L"CannonBoom", targetPos + D3DXVECTOR2(nowScene->GetRandomNumber(-10, 10), nowScene->GetRandomNumber(-50, 50)),
				D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.0f), 0.05f, ri.rotate));

			SoundManager::GetInstance().Play(L"Assets/Sound/Cannon.mp3", false);
		}
	}
	else
		SpawnUI();
}
