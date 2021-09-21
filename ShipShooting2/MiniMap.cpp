#include "DXUT.h"
#include "MiniMap.h"

MiniMap::MiniMap()
{
	miniMap.LoadAll(L"Assets/Sprites/ui/ingame/map.png");
	miniMap.bCamera = false;

	sprites[MINITAG::PLAYER].LoadAll(L"Assets/Sprites/ui/ingame/map/player.png");
	sprites[MINITAG::PLAYER].bCamera = false;

	sprites[MINITAG::ENEMY].LoadAll(L"Assets/Sprites/ui/ingame/map/Enemy.png");
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
	miniMap.Render(RenderInfo{ D3DXVECTOR2(735, -300) });
	for (auto& obj : miniObjects)
	{
		RenderInfo ri;
		if (obj.tag == MINITAG::PLAYER)
			ri.pos = D3DXVECTOR2(745, -415);
		else
			ri.pos = D3DXVECTOR2((obj.pos->x - nowScene->player->pos.x)/ 5 + 735, 
				(obj.pos->y - nowScene->player->pos.y) / 2.8 - 415);

		if(ri.pos.x > 555 && ri.pos.x < 925 &&
			ri.pos.y > -490 && ri.pos.y < -120)
		sprites[obj.tag].Render(ri);
	}
}

void MiniMap::SortObj(Unit* obj)
{
	auto lambda = [=](SpritePos temp)->bool { if (temp.parentUnit == obj) return true; };

	auto mf = std::find(miniObjects.begin(), miniObjects.end(), SpritePos{});

	if(mf != miniObjects.end())
		miniObjects.erase(mf);
}
