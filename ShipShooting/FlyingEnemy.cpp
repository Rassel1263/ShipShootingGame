#include "Header.h"
#include "FlyingEnemy.h"
#include "HomingBullet.h"

FlyingEnemy::FlyingEnemy(D3DXVECTOR2 pos)
{
	type = EnemyType::FlyingEnemy;

	spr.LoadAll(L"Assets/Sprites/Unit/Enemy/Fly");
	SetCollider(-100, -30, 100, 30, L"enemy");
	this->pos = pos;

	attackTime = 3.0f;
}

void FlyingEnemy::Update(float deltaTime)
{
	attackTimer += deltaTime;

	if (attackTimer >= attackTime)
	{
		attackTimer = 0.0f;

		int amount = nowScene->GetRandomNumber(2, 4);
		for (int i = 0; i < amount; ++i)
		{
			float fixRotate = 0.0f;
			if(i > 1)
				 fixRotate = 270 + nowScene->GetRandomNumber(-45, 0);
			else
				fixRotate = 270 + nowScene->GetRandomNumber(0, 45);

			nowScene->obm.AddObject(new HomingBullet(pos + D3DXVECTOR2(20 - 20 * i, 0), nowScene->player, 10, fixRotate, false));
		}
	}

	pos.y -= nowScene->player->ability.speed / 2 * deltaTime;

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

void FlyingEnemy::OnCollision(Collider& coli)
{
	CEnemy::OnCollision(coli);
}
