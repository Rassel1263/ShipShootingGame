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
	if (bulletAmount < 5)
	{
		reloadTimer += deltaTime;
		if (reloadTimer >= reloadTime)
		{
			bulletAmount++;
			reloadTimer = 0.0f;
		}
	}

	shootInterval -= deltaTime;

	D3DXVECTOR2 distance = nowScene->enemy->pos - pos;
	D3DXVec2Normalize(&distance, &distance);
	float angle = atan2(distance.y, distance.x);

	ri.rotate = D3DXToDegree(-angle) + 90;

	CWeapon::Render();
}

void Cannon::Render()
{
	CWeapon::Render();
}

void Cannon::Shoot()
{
	if (bulletAmount > 0)
		if (shootInterval <= 0.0f)
		{
			shootInterval = 1.0f;
			bulletAmount--;
			float radian = D3DXToRadian(-ri.rotate + 80);
			D3DXVECTOR2 fixpos = pos + D3DXVECTOR2(cosf(radian), sinf(radian)) * 13;

			nowScene->obm.AddObject(new Effect(L"CannonShot", fixpos, D3DXVECTOR2(1, 1), 0.05f, ri.rotate, 1, D3DXVECTOR2(0.5f, 0.0f)));
			nowScene->obm.AddObject(new Effect(L"CannonBoom", nowScene->enemy->pos + D3DXVECTOR2(nowScene->GetRandomNumber(-10, 10), nowScene->GetRandomNumber(-100, 100)),
				D3DXVECTOR2(1, 1), 0.05f, ri.rotate, 1, D3DXVECTOR2(0.5f, 0.0f)));
		}
}
