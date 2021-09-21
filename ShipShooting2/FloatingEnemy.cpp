#include "DXUT.h"
#include "FloatingEnemy.h"

FloatingEnemy::FloatingEnemy(D3DXVECTOR2 pos) : CEnemy(pos)
{
	type = EnemyType::FloatingEnemy;
	ability.SetAbility(50, 50);

	Resize(24);

	for (int i = 0; i < 24; ++i)
		GetSprite(i).LoadAll(L"Assets/Sprites/enemy/type1/move/" + std::to_wstring(i));
	//GetSprite(i).LoadAll(L"aa"+ std::to_wstring(i));

	CreateCollider(D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), L"enemy");
}

void FloatingEnemy::Update(float deltaTime)
{
	Move(deltaTime);
	/*float targetAngle = D3DXToRadian(nowScene->GetAngleFromTarget(pos, target->pos));
	std::cout << targetAngle - curRadian << std::endl;*/

	CEnemy::Update(deltaTime);
}

void FloatingEnemy::Render()
{
	CEnemy::Render();
}

void FloatingEnemy::Destroy()
{
	if (!GetNowSprite().bAnimation)
	{
		nowScene->obm.AddObject(new Item(pos, nowScene->GetRandomNumber(0, 5)));
		nowScene->enemyManager.SortEnemy(this, type);

		destroy = true;
	}
}

