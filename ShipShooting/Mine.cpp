#include "Header.h"
#include "Mine.h"
#include "Effect.h"
#include "CBullet.h"

Mine::Mine(D3DXVECTOR2 pos)
{
	this->pos = pos;

	spr.LoadAll(L"Assets/Sprites/Obstacle/mine.png");
	range.LoadAll(L"Assets/Sprites/Obstacle/mineRange.png");

	Collider::AABB aabb;
	aabb.min = { -75, -75};
	aabb.max = { 75, 75};
	bodies.push_back(Collider(L"obstacle", this, &aabb));


	hitTime = 0.1f;

	layer = 6;
}

void Mine::Update(float deltaTime)
{
	if (hp <= 0)
		Destroy();

	if (bHit)
	{
		hitTimer += deltaTime;

		if (hitTimer >= hitTime)
		{
			hitTimer = 0.0f;
			bHit = false;
		}
	}

	pos.y -= nowScene->player->ability.speed / 2 * deltaTime;
}

void Mine::Render()
{
	range.Render(ri);

	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void Mine::OnCollision(Collider& coli)
{
	if (coli.tag == L"allybullet")
	{
		if (static_cast<CBullet*>(coli.obj)->type != CBullet::BulletType::Machinegun) return;

		if (!bHit)
		{
			hp--;
			bHit = true;
		}
	}

	if (coli.tag == L"ally")
	{
		Destroy();
		nowScene->player->Hit(30);
		nowScene->player->speedDown = true;
		nowScene->player->prevSpeed = nowScene->player->ability.speed;
	}
}

void Mine::Destroy()
{
	nowScene->obm.AddObject(new Effect(L"MineBoom", pos, D3DXVECTOR2(1, 1), 0.0f, 1.0f));
	destroy = true;
}
