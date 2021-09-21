#include "DXUT.h"
#include "CEnemy.h"

CEnemy::CEnemy(D3DXVECTOR2 pos)
{
	team = Team::Enemy;
	hitTime = 0.1f;
	target = nowScene->player;

	this->pos = pos;
}

void CEnemy::Update(float deltaTime)
{
	if (ability.hp <= 0)
		Destroy();

	Unit::Update(deltaTime);
}

void CEnemy::Render()
{
	Unit::Render();
}

void CEnemy::OnCollision(Collider& coli)
{
	if (coli.tag == L"allybullet")
	{
		if (type == EnemyType::FloatingEnemy && static_cast<CBullet*>(coli.obj)->type == CBullet::BulletType::Missile) return;
		if (type == EnemyType::FlyingEnemy && static_cast<CBullet*>(coli.obj)->type == CBullet::BulletType::Torpedo) return;

		Hit(static_cast<CBullet*>(coli.obj)->damage);
	}
}

bool CEnemy::Move(float deltaTime)
{
	curRotate = -nowScene->GetAngleFromTarget(pos, target->pos) + 90;  // -90 ~ 270
	
	/*if (curRotate > 270)
		curRotate = -90;
	
	if (curRotate < -90)
		curRotate = 270;*/

	std::cout << curRotate << std::endl;
	
	//SetAni(-curRotate + 90);
	
	curRadian = D3DXToRadian(curRotate);
	//pos += D3DXVECTOR2(cosf(curRadian), sinf(curRadian)) * ability.speed * deltaTime;

	//ri.rotate = -nowScene->GetAngleFromTarget(pos, target->pos) + 90;

	return true;
}

void CEnemy::Hit(float damage)
{
	if (hit) return;

	hit = true;
	this->ability.hp -= damage;

	if (ability.hp <= 0)
	{
		if (type == EnemyType::FloatingEnemy)
		{
			nowScene->obm.AddObject(new Effect(L"onexplode", pos, D3DXVECTOR2(0.4, 0.4), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));

			GetNowSprite().LoadAll(L"Assets/Sprites/enemy/type1/sink/" + std::to_wstring(renderNum), 0.05f, false);
			GetNowSprite().Reset();
		}

		bCollider = false;
		ability.hp = 0;
	}
}

void CEnemy::Destroy()
{
}
