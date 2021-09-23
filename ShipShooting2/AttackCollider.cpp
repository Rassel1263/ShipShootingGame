#include "DXUT.h"
#include "AttackCollider.h"

AttackCollider::AttackCollider(D3DXVECTOR2 pos, D3DXVECTOR2 min, D3DXVECTOR2 max, float damage, float time)
{
	this->pos = pos;
	this->damage = damage;
	this->time = time;

	CreateCollider(min, max, L"hitBox");
}

void AttackCollider::Update(float deltaTime)
{
	time -= deltaTime;

	if (time <= 0.0f)
		destroy = true;
}

void AttackCollider::Render()
{
	Object::Render();
}
