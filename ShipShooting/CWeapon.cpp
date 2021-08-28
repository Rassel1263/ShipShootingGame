#include "Header.h"
#include "CWeapon.h"

CWeapon::CWeapon(Unit* owner, D3DXVECTOR2 offset)
{
	this->owner = owner;
	this->offset = offset;

	layer = 1;
}

void CWeapon::Update(float deltaTime)
{
	
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
