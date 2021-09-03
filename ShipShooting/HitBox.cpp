#include "Header.h"
#include "HitBox.h"

HitBox::HitBox(D3DXVECTOR2 pos, float left, float bottom, float right, float top, float damage, float time)
{
	this->pos = pos;
	this->damage = damage;
	this->time = time;

	Collider::AABB aabb;
	aabb.min = { left, bottom };
	aabb.max = { right, top };

	bodies.push_back(Collider(L"hitbox", this, &aabb));
}

void HitBox::Update(float deltaTime)
{
	time -= deltaTime;

	if (time <= 0.0f)
		destroy = true;
}

void HitBox::Render()
{
	Object::Render();
}

void HitBox::OnCollision(Collider& coli)
{
	if (coli.tag == L"ally")
	{
		nowScene->player->Hit(damage);
	}
}
