#include "DXUT.h"
#include "Map.h"

Map::Map()
{
	ocean.LoadAll(L"Assets/Sprites/map/Ocean", 0.5f);
	ocean.heightRatio = -50.0f;
	ocean.widthRatio = 3.0f;

	shadow.LoadAll(L"Assets/Sprites/map/shadow.png");
	shadow.bCamera = false;

	cloudTimer = 0.0f;
}

void Map::Update(float deltaTime)
{
	cloudTimer -= deltaTime;

	if (cloudTimer <= 0.0f)
	{
		cloudTimer = nowScene->GetRandomNumber(1, 3);
		nowScene->obm.AddObject(new Cloud(D3DXVECTOR2(nowScene->GetRandomNumber(-1500, 1500), Camera::GetInstance().cameraPos.y + 900)));
	} 
}

void Map::Render()
{
	ocean.Render(RenderInfo{D3DXVECTOR2(-1920, 0)});
	//shadow.Render(RenderInfo{});
}
