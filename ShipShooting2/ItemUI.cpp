#include "DXUT.h"
#include "ItemUI.h"

ItemUI::ItemUI(int index, D3DXVECTOR2 pos)
{
	this->pos = pos;

	spr.LoadAll(L"Assets/Sprites/Item/" + std::to_wstring(index));
	spr.color.a = 0.7f;
}

void ItemUI::Update(float deltaTime)
{
	D3DXVECTOR2 destPos = D3DXVECTOR2(nowScene->player->pos.x, nowScene->player->pos.y + 350);

	D3DXVec2Lerp(&pos, &pos, &destPos, 0.1f);
	D3DXVec2Lerp(&ri.scale, &ri.scale, &D3DXVECTOR2(2.5, 2.5), 0.1f);

	if (abs(destPos.x - pos.x) <= 5.0f || abs(destPos.y - pos.y) <= 5.0f)
		draw = false;

	if (!draw)
	{
		spr.color.a -= deltaTime;

		if (spr.color.a <= 0.0f)
			destroy = true;
	}
}

void ItemUI::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
