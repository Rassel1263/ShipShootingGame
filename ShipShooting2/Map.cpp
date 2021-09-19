#include "DXUT.h"
#include "Map.h"

Map::Map()
{
	ocean.LoadAll(L"Assets/Sprites/map/Ocean", 0.5f);
	ocean.heightRatio = -50.0f;
	ocean.widthRatio = 3.0f;

	/*shadow.LoadAll(L"Assets/Sprites/map/shadow.png");
	shadow.bCamera = false;*/
}

void Map::Update(float deltaTime)
{
}

void Map::Render()
{
	ocean.Render(RenderInfo{D3DXVECTOR2(-1920, 0)});
	//shadow.Render(RenderInfo{});
}
