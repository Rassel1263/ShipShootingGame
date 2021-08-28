#include "Header.h"
#include "CBullet.h"

CBullet::CBullet(D3DXVECTOR2 pos)
{
	spr.LoadAll(L"Assets/Sprites/a.png");
	this->pos = pos;
}

void CBullet::Update(float deltaTime)
{
	if (pos.x <= -900 || pos.x >= 900 || pos.y <= -600 || pos.y >= 600)
		destroy = true;
}

void CBullet::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
