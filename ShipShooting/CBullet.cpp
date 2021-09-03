#include "Header.h"
#include "CBullet.h"

CBullet::CBullet(D3DXVECTOR2 pos, Unit* target, float damage)
{
	this->pos = pos;
	this->target = target;
	this->damage = damage;

	if (target)
	{
		if (target->team == Team::Ally)
			team = L"enemy";
		if (target->team == Team::Enemy)
			team = L"ally";
	}
	else
		team = L"ally";
	
	layer = 5;
}

void CBullet::Update(float deltaTime)
{
	if (pos.x <= -1200 || pos.x >= 1200 || pos.y <= -600 || pos.y >= 600)
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
	//if (!target) return;

	if (target)
	{
		if (team == L"ally")
		{
			if (type == BulletType::Torpedo && static_cast<CEnemy*>(coli.obj)->type != EnemyType::FloatingEnemy) return;
			if (type == BulletType::Missile && static_cast<CEnemy*>(coli.obj)->type != EnemyType::FlyingEnemy) return;
		}

		if ((target->team == Team::Enemy && coli.tag == L"enemy") || (target->team == Team::Ally && coli.tag == L"ally"))
		{
			CreateEffect();
			destroy = true;
		}
	}

}

void CBullet::SetCollider(float left, float bottom, float right, float top)
{
	Collider::AABB aabb;
	aabb.min = { left, bottom };
	aabb.max = { right, top };
	bodies.push_back(Collider(team + L"bullet", this, &aabb));
}

