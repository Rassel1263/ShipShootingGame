#include "Header.h"
#include "Unit.h"

Unit::Unit()
{
}

void Unit::Update(float deltaTime)
{
}

void Unit::Render()
{
	Object::Render();
}

void Unit::SetAbility(float hp, float speed)
{
	this->ability.hp = hp;
	this->ability.maxHp = hp;
	this->ability.speed = speed;
}

void Unit::SetCollider(float left, float bottom, float right, float top, std::wstring tag)
{
	Collider::AABB aabb;
	aabb.min = { left, bottom };
	aabb.max = { right, top };
	bodies.push_back(Collider(tag, this, &aabb));
}

void Unit::SetCollider(float radius, std::wstring tag)
{
	Collider::Circle circle;
	circle.radius = radius;
	bodies.push_back(Collider(tag, this, 0, &circle));
}


D3DXVECTOR2 Unit::CheckPos()
{
	return D3DXVECTOR2(0, 0);
}
