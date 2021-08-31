#include "Header.h"
#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(D3DXVECTOR2 pos)
{
	type = EnemyType::FloatingEnemy;

	spr.LoadAll(L"Assets/Sprites/Unit/Enemy/Fly");
	SetCollider(-100, -30, 100, 30, L"enemy");
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

void FlyingEnemy::Destroy()
{
	CEnemy::Destroy();
}
