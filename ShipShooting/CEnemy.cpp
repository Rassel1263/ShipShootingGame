#include "Header.h"
#include "CEnemy.h"
#include "CBullet.h"

CEnemy::CEnemy()
{
	team = Team::Enemy;
	spr.LoadAll(L"Assets/Sprites/Unit/Enemy/MarineUnit");

	SetAbility(30, 100);

	colorShader = new ColorShader();

	hitTime = 0.1f;
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

	//pos.y -= nowScene->player->ability.speed / 2* deltaTime;

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
		if(!bHit)
			Hit(static_cast<CBullet*>(coli.obj)->damage);
	}
}

void CEnemy::Destroy()
{
	destroy = true;
	
	nowScene->enemyManager.SortEnemyGroups(this, type);
}

void CEnemy::CheckPos()
{
	if (pos.y <= -400)
	{
		nowScene->enemyManager.SortEnemyGroups(this, type);
		destroy = true;
	}
}

void CEnemy::Hit(float damage)
{
	bHit = true;
	ability.hp -= damage;
}

