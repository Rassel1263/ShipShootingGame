#include "Header.h"
#include "Mine.h"
#include "Effect.h"

Mine::Mine(D3DXVECTOR2 pos)
{
	this->pos = pos;

	spr.LoadAll(L"Assets/Sprites/Obstacle/mine.png");
	range.LoadAll(L"Assets/Sprites/Obstacle/mineRange.png");

	Collider::AABB aabb;
	aabb.min = { -10, -10 };
	aabb.max = { 10, 10 };
	bodies.push_back(Collider(L"mine", this, &aabb));
}

void Mine::Update(float deltaTime)
{
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
	if (coli.tag == L"ally")
	{
		nowScene->obm.AddObject(new Effect(L"MineBoom", pos, D3DXVECTOR2(1, 1), 0.0f, 1.0f));
		destroy = true;
	}
}
