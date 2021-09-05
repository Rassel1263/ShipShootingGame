#include "Header.h"
#include "SubFlyingEnemy.h"

SubFlyingEnemy::SubFlyingEnemy(D3DXVECTOR2 pos) : FlyingEnemy(pos)
{
	spr.LoadAll(L"Assets/Sprites/Unit/Enemy/Sub");
}

void SubFlyingEnemy::Update(float deltaTime)
{
	pos += D3DXVECTOR2(cosf(angle), sinf(angle));

	CEnemy::Update(deltaTime);
}

void SubFlyingEnemy::Render()
{
	CEnemy::Render();
}

void SubFlyingEnemy::Destroy()
{
}
