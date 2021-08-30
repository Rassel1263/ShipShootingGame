#include "Header.h"
#include "MachinegunBullet.h"
#include "Effect.h"

MachinegunBullet::MachinegunBullet(D3DXVECTOR2 pos, Unit* target) : CBullet(pos, target)
{
	spr.LoadAll(L"Assets/Sprites/Unit/Bullet/machine.png");

	if (target)
	{
		D3DXVECTOR2 distance = target->pos - pos;
		D3DXVec2Normalize(&distance, &distance);
		angle = atan2(distance.y, distance.x);
	}

	SetCollider(-3, -3, 3, 3);
	ri.rotate = D3DXToDegree(-angle);
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
	nowScene->obm.AddObject(new Effect(L"Machinegun", pos, D3DXVECTOR2(1, 1), 0.05f, 0, 1));
}
