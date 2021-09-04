#include "Header.h"
#include "Mine.h"
#include "Effect.h"
#include "CBullet.h"
#include "Item.h"

Mine::Mine(D3DXVECTOR2 pos)
{
	this->pos = pos;

	spr.LoadAll(L"Assets/Sprites/Obstacle/Mine");
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
		Destroy(false);

	if (bHit)
	{
		hitTimer += deltaTime;

		if (hitTimer >= hitTime)
		{
			hitTimer = 0.0f;
			bHit = false;
		}
	}

	pos.y -= nowScene->player->ability.speed / 2.5 * deltaTime;

	spr.Update(deltaTime);

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
		Destroy(true);
		nowScene->player->Hit(30);
		nowScene->player->speedDown = true;
		nowScene->player->prevSpeed = nowScene->player->ability.speed;
	}

}

void Mine::Destroy(bool explosion)
{
	if(!explosion)
		nowScene->obm.AddObject(new Item(pos, nowScene->GetRandomNumber(0, 5)));

	nowScene->obm.AddObject(new Effect(L"Mine", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 0.05f, 0));
	destroy = true;
}
