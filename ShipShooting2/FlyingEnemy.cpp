#include "DXUT.h"
#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(D3DXVECTOR2 pos) : CEnemy(pos)
{
	Resize(24);

	for (int i = 0; i < 24; ++i)
		GetSprite(i).LoadAll(L"aa" + std::to_wstring(i));
	//GetSprite(i).LoadAll(L"Assets/Sprites/enemy/type2/move/" + std::to_wstring(i));

	CreateCollider(D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), L"enemy");
}

void FlyingEnemy::Update(float deltaTime)
{
	CEnemy::Update(deltaTime);
}

void FlyingEnemy::Render()
{
	CEnemy::Render();
}

void FlyingEnemy::OnCollision(Collider& coli)
{
}

void FlyingEnemy::Destroy()
{
}
