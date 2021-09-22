#include "DXUT.h"
#include "MachinegunBullet.h"

MachinegunBullet::MachinegunBullet(D3DXVECTOR2 pos, Unit* target, std::wstring tag, float damage, float speed)
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

void MachinegunBullet::Update(float deltaTime)
{
	CBullet::Update(deltaTime);
}

void MachinegunBullet::Render()
{
	CBullet::Render();
}

void MachinegunBullet::CreateEffect()
{
	nowScene->obm.AddObject(new Effect(L"Hit_machinegun/", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f, -nowScene->GetAngleFromTarget(pos, target->pos) + 90));
}
