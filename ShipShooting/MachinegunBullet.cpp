#include "Header.h"
#include "MachinegunBullet.h"

MachinegunBullet::MachinegunBullet(D3DXVECTOR2 pos) : CBullet(pos)
{
	spr.LoadAll(L"Assets/Sprites/Unit/Bullet/machine.png");

	D3DXVECTOR2 distance = nowScene->enemy->pos - pos;
	D3DXVec2Normalize(&distance, &distance);
	angle = atan2(distance.y, distance.x);

	ri.rotate = D3DXToDegree(-angle);
}

void MachinegunBullet::Update(float deltaTime)
{
	pos += D3DXVECTOR2(cosf(angle), sinf(angle)) * 500 * deltaTime;

	CBullet::Update(deltaTime);
}

void MachinegunBullet::Render()
{
	CBullet::Render();
}
