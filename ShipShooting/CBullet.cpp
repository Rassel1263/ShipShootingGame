#include "Header.h"
#include "CBullet.h"

CBullet::CBullet(D3DXVECTOR2 pos, Unit* target)
{
	spr.LoadAll(L"Assets/Sprites/a.png");
	this->pos = pos;
	this->target = target;
}

void CBullet::Update(float deltaTime)
{
	if (pos.x <= -900 || pos.x >= 900 || pos.y <= -600 || pos.y >= 600)
		destroy = true;

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
	if (coli.tag == L"enemy")
	{
		CreateEffect();
		destroy = true;
	}
}

void CBullet::SetCollider(float left, float bottom, float right, float top)
{
	Collider::AABB aabb;
	aabb.min = { left, bottom };
	aabb.max = { right, top };
	bodies.push_back(Collider(L"bullet", this, &aabb));
}

