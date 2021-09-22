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
	if (sprites[MINITAG::ENEMY].color.a >= 1.0f || sprites[MINITAG::ENEMY].color.a <= 0.0f)
		destColor = -destColor;

	sprites[MINITAG::ENEMY].color.a += deltaTime * destColor * 1.5f;
	sprites[MINITAG::ENEMY].color.a = std::clamp(sprites[MINITAG::ENEMY].color.a, 0.0f, 1.0f);


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
	auto lambda = [=](SpritePos temp)->bool { 
		if (temp.parentUnit == obj)
			return true;

		return false;
	};

	auto mf = std::find_if(miniObjects.begin(), miniObjects.end(), lambda);

	if(mf != miniObjects.end())
		miniObjects.erase(mf);
}

