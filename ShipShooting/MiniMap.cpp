#include "Header.h"
#include "MiniMap.h"

void MiniMap::Init()
{
	sprites[MINITAG::PLAYER].LoadAll(L"Assets/Sprites/UI/MiniMap/player.png");
	sprites[MINITAG::PLAYER].bCamera = false;
	sprites[MINITAG::ENEMY].LoadAll(L"Assets/Sprites/UI/MiniMap/enemy.png");
	sprites[MINITAG::ENEMY].bCamera = false;

	minimap.LoadAll(L"Assets/Sprites/UI/MiniMap/bck.png");
	minimap.bCamera = false;
}

void MiniMap::AddMiniObject(MINITAG tag, D3DXVECTOR2* pos, Object* parentObj)
{
	addObjects.push_back({ tag, pos, parentObj });
}

void MiniMap::Update(float deltaTime)
{
	miniObjects.insert(miniObjects.end(), addObjects.begin(), addObjects.end());
	addObjects.clear();
}

void MiniMap::Render()
{
	minimap.Render(RenderInfo{D3DXVECTOR2(700, 300)});

	for (auto& object : miniObjects)
	{
		RenderInfo ri;
		ri.pos = *(object).pos / 7.5 + D3DXVECTOR2(700, 250);

		sprites[object.tag].Render(ri);
	}
}

void MiniMap::Term(Object* obj)
{
	for (auto it = miniObjects.begin(); it != miniObjects.end();)
	{
		if ((*it).parentObj == obj)
			it = miniObjects.erase(it);
		else
			++it;
	}
}

void MiniMap::ChangeScene()
{
	miniObjects.clear();
	addObjects.clear();
}
