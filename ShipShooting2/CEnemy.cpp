#include "DXUT.h"
#include "CEnemy.h"

CEnemy::CEnemy(D3DXVECTOR2 pos)
{
	team = Team::Enemy;
	hitTime = 0.1f;
	target = nowScene->player;
	turnSpeed = D3DXToRadian(5);

	this->pos = pos;
}

void CEnemy::Update(float deltaTime)
{
	if (ability.hp <= 0)
		Destroy();
	else
		Move(deltaTime);

	if (nowScene->spawnBoss)
	{
		if (type == EnemyType::FloatingEnemy || type == EnemyType::FlyingEnemy)
		{
			nowScene->obm.AddObject(new Effect(L"onexplode", pos, D3DXVECTOR2(0.4, 0.4), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
			nowScene->enemyManager.SortEnemy(this, type);
			destroy = true;
		}
	}

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
	float targetAngle = D3DXToRadian(nowScene->GetAngleFromTarget(pos, target->pos));  // -90 ~ 270 
	float diff = targetAngle - curRadian;


	if (type == EnemyType::FlyingEnemy)
	{
		if (attackTimer >= attackTime)
			turnTime += deltaTime;
	}
	else
		turnTime += deltaTime;

	if (turnTime >= 0.01f)
	{
		if (diff > D3DX_PI)
			diff -= D3DX_PI * 2;
		else if (diff < -D3DX_PI)
			diff += D3DX_PI * 2;

		if (diff > turnSpeed)
			curRadian += turnSpeed;
		else if (diff < -turnSpeed)
			curRadian -= turnSpeed;
		else
		{
			Attack(deltaTime);
			curRadian = targetAngle;
		}

		turnTime = 0.0f;
	}

	SetAni(D3DXToDegree(-curRadian) + 450);
	
	pos += D3DXVECTOR2(cosf(curRadian), sinf(curRadian)) * ability.speed * deltaTime;

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
			SoundManager::GetInstance().Play(L"explo");
			nowScene->AddScore(nowScene->GetRandomNumber(1000, 2000));
			nowScene->obm.AddObject(new Effect(L"onexplode", pos, D3DXVECTOR2(0.4, 0.4), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));

			GetNowSprite().LoadAll(L"Assets/Sprites/enemy/type1/sink/" + std::to_wstring(renderNum), 0.03f, false);
			GetNowSprite().Reset();
		}

		bCollider = false;
		ability.hp = 0;
	}
}

void CEnemy::Attack(float deltaTime)
{
}

void CEnemy::Destroy()
{
	nowScene->enemyManager.SortEnemy(this, type);
	destroy = true;
}
