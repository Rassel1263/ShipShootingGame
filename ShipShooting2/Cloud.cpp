#include "DXUT.h"
#include "Cloud.h"

Cloud::Cloud(D3DXVECTOR2 pos)
{
	this->pos = pos;
	spr.LoadAll(L"Assets/Sprites/Cloud/" + std::to_wstring(nowScene->GetRandomNumber(0, 3)) + L".png");
	this->speed = nowScene->GetRandomNumber(50, 150);

	layer = 15;
}

void Cloud::Update(float deltaTime)
{
	pos.y -= deltaTime * speed;

	if (pos.y < Camera::GetInstance().cameraPos.y - 800)
		destroy = true;
}

void Cloud::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}
