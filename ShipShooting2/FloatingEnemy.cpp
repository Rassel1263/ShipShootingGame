#include "DXUT.h"
#include "FloatingEnemy.h"

FloatingEnemy::FloatingEnemy(D3DXVECTOR2 pos) : CEnemy(pos)
{
	attackTime = 1.0f;

	type = EnemyType::FloatingEnemy;
	ability.SetAbility(50, 200);

	Resize(24);

	for (int i = 0; i < 24; ++i)
		GetSprite(i).LoadAll(L"Assets/Sprites/enemy/type1/move/" + std::to_wstring(i));

	SetAni(-nowScene->GetAngleFromTarget(pos, target->pos) + 450);
	CreateCollider(D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), L"enemy");
}

void FloatingEnemy::Update(float deltaTime)
{
	if (pos.y < Camera::GetInstance().cameraPos.y - 600)
	{
		nowScene->enemyManager.SortEnemy(this, type);
		destroy = true;
	}

	CEnemy::Update(deltaTime);
}

void FloatingEnemy::Render()
{
	CEnemy::Render();
}

void FloatingEnemy::OnCollision(Collider& coli)
{
	if (coli.tag == L"obstacle")
	{
		if (static_cast<Obstacle*>(coli.obj)->type == Obstacle::ObstalceType::ROCK)
		{
			nowScene->obm.AddObject(new Effect(L"onexplode", pos, D3DXVECTOR2(0.4, 0.4), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
			CEnemy::Destroy();
		}
	}

	if (coli.tag == L"player")
	{
		if(type == EnemyType::FloatingEnemy)
			Hit(ability.maxHp);

		nowScene->player->Hit(20);
	}

	CEnemy::OnCollision(coli);
}

void FloatingEnemy::Destroy()
{
	if (!GetNowSprite().bAnimation)
	{

		if (nowScene->GetRandomNumber(0, 3))
			nowScene->obm.AddObject(new Item(pos, nowScene->GetRandomNumber(0, 5)));
		else
			nowScene->obm.AddObject(new Obstacle(pos, Obstacle::ObstalceType::MINE));

		nowScene->player->kills++;

		CEnemy::Destroy();
	}
}

void FloatingEnemy::Attack(float deltaTime)
{
	attackTimer += deltaTime;

	if (attackTimer >= attackTime)
	{
		D3DXVECTOR2 fixPos = pos + D3DXVECTOR2(cosf(curRadian), sinf(curRadian)) * 50;

		nowScene->obm.AddObject(new HomingBullet(fixPos, target, CBullet::BulletType::Torpedo, L"enemy", 10, D3DXToDegree(-curRadian) + 90, 0.0f, 700));
		attackTimer = 0.0f;
	}
}

