#include "Header.h"
#include "CWeapon.h"

CWeapon::CWeapon(Unit* owner, D3DXVECTOR2 offset)
{
	this->owner = owner;
	this->offset = offset;

	layer = owner->layer + 1;
}

void CWeapon::Update(float deltaTime)
{
	if (shootTimer < shootInterval)
		shootTimer += deltaTime;

	if (uiTime > 0.0f)
		uiTime -= deltaTime;
}

void CWeapon::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void CWeapon::Shoot()
{
}

void CWeapon::SpawnUI()
{
	if (uiTime <= 0.0f)
	{
		uiTime = 2.0f;
		Camera::GetInstance().cameraQuaken = { 4, 4 };
		nowScene->obm.AddObject(new Effect(L"lackOfBullet.png", D3DXVECTOR2(0, -445), D3DXVECTOR2(2, 2), 0, 2.0f, false));
	}
}
