#include "DXUT.h"
#include "MiniMap.h"

MiniMap::MiniMap()
{
	miniMap.LoadAll(L"Assets/Sprites/ui/ingame/map.png");
	miniMap.bCamera = false;

	sprites[MINITAG::PLAYER].LoadAll(L"Assets/Sprites/ui/ingame/map/player.png");
	sprites[MINITAG::PLAYER].bCamera = false;

	sprites[MINITAG::ENEMY].LoadAll(L"Assets/Sprites/ui/ingame/map/Enemy.png.png");
	sprites[MINITAG::ENEMY].bCamera = false;
}

void MiniMap::AddMiniObj(MINITAG tag, D3DXVECTOR2* pos, Unit* parent)
{
	miniObjects.push_back({ tag, pos, parent });
}

void MiniMap::Update(float deltaTime)
{
}

void MiniMap::Render()
{
	miniMap.Render(RenderInfo{ D3DXVECTOR2(700, -300) });
	for (auto& obj : miniObjects)
	{
		RenderInfo ri;
		ri.pos = D3DXVECTOR2(obj.pos->x / 5 + 700, obj.pos->y / 2.8 - 300);
		sprites[obj.tag].Render(ri);
	}
}

void MiniMap::SortObj(Unit* obj)
{
}
