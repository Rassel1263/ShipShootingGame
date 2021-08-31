#include "Header.h"
#include "CEnemy.h"
#include "CBullet.h"

CEnemy::CEnemy()
{
	team = Team::Enemy;
	spr.LoadAll(L"Assets/Sprites/Unit/Enemy/MarineUnit");

	SetAbility(30, 100);
	this->pos = { 0, 200 };
}

void CEnemy::Update(float deltaTime)
{
	if (ability.hp <= 0)
		Destroy();

	pos.y -= nowScene->player->ability.speed / 2* deltaTime;

	spr.Update(deltaTime);
}

void CEnemy::Render()
{
	ri.pos = pos;
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
		Hit(static_cast<CBullet*>(coli.obj)->damage);
	}
}

void CEnemy::Destroy()
{
	destroy = true;
	
	nowScene->enemyManager.SortEnemyGroups(this, type);
}

void CEnemy::Hit(float damage)
{
	ability.hp -= damage;

}

