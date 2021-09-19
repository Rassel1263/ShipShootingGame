#include "DXUT.h"
#include "CBullet.h"

CBullet::CBullet(D3DXVECTOR2 pos, Unit* target, float damage)
{
	this->pos = pos;
	this->target = target;
	this->damage = damage;

	spr.LoadAll(L"Assets/Sprites/bullet/machinegunBullet/");

	CreateCollider(D3DXVECTOR2(-5, -5), D3DXVECTOR2(5, 5), L"ally");
}

void CBullet::Update(float deltaTime)
{
	pos.y += deltaTime * 100;

	spr.Update(deltaTime);
}

void CBullet::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void CBullet::OnCollision(Collider& coli)
{
}
