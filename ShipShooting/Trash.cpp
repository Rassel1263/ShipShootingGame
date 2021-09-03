#include "Header.h"
#include "Trash.h"
#include "CBullet.h"

Trash::Trash(D3DXVECTOR2 pos)
{
	spr.LoadAll(L"Assets/Sprites/Obstacle/trash.png");
	this->pos = pos;

	Collider::AABB aabb;
	aabb.min = { -50, -50 };
	aabb.max = { 50, 50 };
	bodies.push_back(Collider(L"obstacle", this, &aabb));
	
	layer = 4;
}

void Trash::Update(float deltaTime)
{
	if (hp <= 0)
		destroy = true;

	if (bHit)
	{
		spr.color.a = 0.0f;
		hitTimer += deltaTime;

		if (hitTimer >= hitTime)
		{
			spr.color.a = 1.0f;
			hitTimer = 0.0f;
			bHit = false;
		}
	}

	pos.y -= nowScene->player->ability.speed / 3 * deltaTime;
}

void Trash::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void Trash::OnCollision(Collider& coli)
{
	if (coli.tag == L"allybullet")
	{
		if (static_cast<CBullet*>(coli.obj)->type == CBullet::BulletType::Missile) return;

		if (!bHit)
		{
			hp--;
			bHit = true;
		}
	}

	if (coli.tag == L"ally")
	{
		if (!nowScene->player->speedDown)
		{
			nowScene->player->prevSpeed = nowScene->player->ability.speed;
			nowScene->player->speedDown = true;
		}
	}
}
