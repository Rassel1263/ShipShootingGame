#include "Header.h"
#include "CEnemy.h"
#include "CBullet.h"
#include "Item.h"
#include "Effect.h"

CEnemy::CEnemy()
{
	team = Team::Enemy;
	spr.LoadAll(L"Assets/Sprites/Unit/Enemy/MarineUnit");

	SetAbility(30, 100);

	colorShader = new ColorShader();

	hitTime = 0.1f;

	MiniMap::GetInstance().AddMiniObject(MINITAG::ENEMY, &pos, this);
}

void CEnemy::Update(float deltaTime)
{
	if (ability.hp <= 0)
		Destroy();

	CheckPos();

	if (bHit)
	{
		hitTimer += deltaTime;

		if (hitTimer >= hitTime)
		{
			hitTimer = 0.0f;
			bHit = false;
		}
	}


	spr.Update(deltaTime);
}

void CEnemy::Render()
{
	ri.pos = pos;

	if (bHit)
		colorShader->Render(colorShader, spr, ri, D3DXVECTOR4(0.5, 0, 0, 1));
	else
		spr.Render(ri);
	
	Object::Render();
}

bool CEnemy::Move(float deltaTime)
{
	return false;
}

void CEnemy::OnCollision(Collider& coli)
{
	if (coli.tag == L"allybullet")
	{
		if (type == EnemyType::FloatingEnemy && static_cast<CBullet*>(coli.obj)->type == CBullet::BulletType::Missile) return;
		if (type == EnemyType::FlyingEnemy && static_cast<CBullet*>(coli.obj)->type == CBullet::BulletType::Torpedo) return;

		if(!bHit)
			Hit(static_cast<CBullet*>(coli.obj)->damage);
	}
}

void CEnemy::Destroy()
{
	nowScene->obm.AddObject(new Effect(L"Die/0", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), 0.05f, 0));
	nowScene->obm.AddObject(new Item(pos, nowScene->GetRandomNumber(0, 5)));
	nowScene->AddScore(nowScene->GetRandomNumber(500, 1000));
	nowScene->enemyManager.SortEnemyGroups(this, type);
	MiniMap::GetInstance().Term(this);

	destroy = true;
	
}

void CEnemy::CheckPos()
{
	if (pos.y <= -700)
	{
		nowScene->enemyManager.SortEnemyGroups(this, type);
		MiniMap::GetInstance().Term(this);
		destroy = true;
	}
}

void CEnemy::Hit(float damage)
{
	bHit = true;
	ability.hp -= damage;
}

