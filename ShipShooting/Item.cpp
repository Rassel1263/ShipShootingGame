#include "Header.h"
#include "Item.h"

Item::Item(D3DXVECTOR2 pos, int index)
{
	this->pos = pos;
	this->index = index;

	spr.LoadAll(L"Assets/Sprites/UI/Item/" + std::to_wstring(index) + L".png");

	Collider::AABB aabb;
	aabb.min = { -30, -30 };
	aabb.max = { 30, 30 };

	bodies.push_back(Collider(L"item", this, &aabb));

	layer = 6;
}

void Item::Update(float deltaTime)
{
	pos.y -= 100 * deltaTime;
}

void Item::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void Item::OnCollision(Collider& coli)
{
	if (coli.tag == L"ally")
	{
		nowScene->player->GetItemEffective(index);
		destroy = true;
	}
}
