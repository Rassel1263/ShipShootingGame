#include "Header.h"
#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(D3DXVECTOR2 pos)
{
	spr.LoadAll(L"Assets/Sprites/Unit/Enemy/Fly");
	SetCollider(-100, -30, 100, 30);
	this->pos = pos;
}

void FlyingEnemy::Update(float deltaTime)
{
	CEnemy::Update(deltaTime);
}

void FlyingEnemy::Render()
{
	CEnemy::Render();
}
