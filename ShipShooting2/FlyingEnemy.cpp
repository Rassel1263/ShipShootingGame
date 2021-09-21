#include "DXUT.h"
#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(D3DXVECTOR2 pos) : CEnemy(pos)
{
	type = EnemyType::FlyingEnemy;
	ability.SetAbility(100, 200);
	attackTime = 3.0f;
	attackTimer = 3.0f;

	Resize(24);

	for (int i = 0; i < 24; ++i)
		GetSprite(i).LoadAll(L"Assets/Sprites/enemy/type2/move/" + std::to_wstring(i));

		//GetSprite(i).LoadAll(L"aa" + std::to_wstring(i));

	CreateCollider(D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), L"enemy");
}

void FlyingEnemy::Update(float deltaTime)
{
	attackTimer += deltaTime;

	CEnemy::Update(deltaTime);
}

void FlyingEnemy::Render()
{
	CEnemy::Render();
}

void FlyingEnemy::Destroy()
{
	nowScene->obm.AddObject(new Item(pos, nowScene->GetRandomNumber(0, 5)));
	nowScene->enemyManager.SortEnemy(this, type);
	destroy = true;
}

void FlyingEnemy::Attack(float deltaTime)
{
	if (attackTimer >= attackTime)
	{
		int num = nowScene->GetRandomNumber(3, 4);
		for (int i = 0; i < num; ++i)
			nowScene->obm.AddObject(new HomingBullet(pos, target, CBullet::BulletType::Missile, L"enemy", 10,
				D3DXToDegree(-curRadian) + 90 + nowScene->GetRandomNumber(-45, 45)));

		attackTimer = 0.0f;
	}
}
