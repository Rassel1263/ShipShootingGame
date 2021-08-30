#include "Header.h"
#include "FloatingEnemy.h"

FloatingEnemy::FloatingEnemy(D3DXVECTOR2 pos)
{
	spr.LoadAll(L"Assets/Sprites/Unit/Enemy/Float");
	SetCollider(-30, -100, 30, 100);
	this->pos = pos;
}

void FloatingEnemy::Update(float deltaTime)
{
	CEnemy::Update(deltaTime);
}

void FloatingEnemy::Render()
{
	CEnemy::Render();
}
