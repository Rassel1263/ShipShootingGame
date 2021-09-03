#include "Header.h"
#include "MachinegunBullet.h"
#include "Effect.h"

MachinegunBullet::MachinegunBullet(D3DXVECTOR2 pos, Unit* target, float damage) : CBullet(pos, target, damage)
{
	type = BulletType::Machinegun;

	spr.LoadAll(L"Assets/Sprites/Unit/Bullet/machine.png");

	if (target)
	{
		D3DXVECTOR2 distance = target->pos - pos;
		D3DXVec2Normalize(&distance, &distance);
		angle = atan2(distance.y, distance.x);
	}
	else
		angle = D3DXToRadian(90);

	ri.rotate = D3DXToDegree(-angle);
	SetCollider(-3, -3, 3, 3);
}

void MachinegunBullet::Update(float deltaTime)
{
	pos += D3DXVECTOR2(cosf(angle), sinf(angle)) * 1000 * deltaTime;

	CBullet::Update(deltaTime);
}

void MachinegunBullet::Render()
{
	CBullet::Render();
}

void MachinegunBullet::CreateEffect()
{
	nowScene->obm.AddObject(new Effect(L"Machinegun", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), 0.05f, 0));
}

void MachinegunBullet::OnCollision(Collider& coli)
{
	CBullet::OnCollision(coli);

	if (coli.tag == L"obstacle")
	{
		CreateEffect();
		destroy = true;
	}
}
