#include "Header.h"
#include "CEnemy.h"

CEnemy::CEnemy()
{
	spr.LoadAll(L"Assets/Sprites/Unit/Enemy/MarineUnit");
	this->pos = { 0, 200 };
}

void CEnemy::Update(float deltaTime)
{
	//pos.y -= nowScene->player->ability.speed / 2* deltaTime;

	spr.Update(deltaTime);
}

void CEnemy::Render()
{
	ri.pos = pos;
	spr.Render(ri);
	
	Object::Render();
}

bool CEnemy::Move(float deltaTime)
{
	return false;
}

void CEnemy::SetCollider(float left, float bottom, float right, float top)
{
	Collider::AABB aabb;
	aabb.min = { left, bottom };
	aabb.max = { right, top};
	bodies.push_back(Collider(L"enemy", this, &aabb));
}
