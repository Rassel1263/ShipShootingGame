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
