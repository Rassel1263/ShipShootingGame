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
}

void Unit::SetAbility(float hp, float speed)
{
	this->ability.hp = hp;
	this->ability.maxHp = hp;
	this->ability.speed = speed;
}

D3DXVECTOR2 Unit::CheckPos()
{
	return D3DXVECTOR2(0, 0);
}
