#include "DXUT.h"
#include "FloatingEnemy.h"

FloatingEnemy::FloatingEnemy(D3DXVECTOR2 pos) : CEnemy(pos)
{
	Resize(24);

	for (int i = 0; i < 24; ++i)
		GetSprite(i).LoadAll(L"aa"+ std::to_wstring(i));
		//GetSprite(i).LoadAll(L"Assets/Sprites/enemy/type1/move/" + std::to_wstring(i));

	CreateCollider(D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), L"enemy");
}

void FloatingEnemy::Update(float deltaTime)
{
	CEnemy::Update(deltaTime);
}

void FloatingEnemy::Render()
{
	CEnemy::Render();
}

void FloatingEnemy::OnCollision(Collider& coli)
{
}

void FloatingEnemy::Destroy()
{
}
