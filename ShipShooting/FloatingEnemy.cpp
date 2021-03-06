#include "Header.h"
#include "FloatingEnemy.h"
#include "Torpedo.h"
#include "Mine.h"

FloatingEnemy::FloatingEnemy(D3DXVECTOR2 pos)
{
	type = EnemyType::FloatingEnemy;

	spr.LoadAll(L"Assets/Sprites/Unit/Enemy/Float");
	SetCollider(-30, -100, 30, 100, L"enemy");
	this->pos = pos;

	attackTime = 3.0f;
}

void FloatingEnemy::Update(float deltaTime)
{
	attackTimer += deltaTime;

	if (attackTimer >= attackTime)
	{
		attackTimer = 0.0f;

		nowScene->obm.AddObject(new Torpedo(pos, nowScene->player, 20));
	}

	pos.y -= nowScene->player->ability.speed / 2* deltaTime;

	CEnemy::Update(deltaTime);
}

void FloatingEnemy::Render()
{
	CEnemy::Render();
}

void FloatingEnemy::Destroy()
{
	int n = nowScene->GetRandomNumber(0, 0);
	if (!n) nowScene->obm.AddObject(new Mine(pos));

	CEnemy::Destroy();
}

void FloatingEnemy::OnCollision(Collider& coli)
{
	if (coli.tag == L"ally")
	{
		nowScene->player->Hit(30);
		CEnemy::Destroy();
	}

	CEnemy::OnCollision(coli);
}

