#include "DXUT.h"
#include "NavalgunBullet.h"

NavalgunBullet::NavalgunBullet(D3DXVECTOR2 pos, Unit* target, std::wstring tag, float damage, float speed)
	:CBullet(pos, target, tag, damage)
{
	type = BulletType::Machinegun;
	this->speed = speed;

	spr.LoadAll(L"Assets/Sprites/bullet/machinegunBullet/");

	if (target)
	{
		D3DXVECTOR2 distance = target->pos - pos;
		angle = atan2(distance.y, distance.x);
	}
	else
		angle = D3DXToRadian(90);

	ri.rotate = D3DXToDegree(-angle) + 90;
}

void NavalgunBullet::Update(float deltaTime)
{
	CBullet::Update(deltaTime);
}

void NavalgunBullet::Render()
{
	CBullet::Render();
}

void NavalgunBullet::CreateEffect()
{

}

