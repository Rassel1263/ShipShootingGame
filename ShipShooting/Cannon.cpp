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
