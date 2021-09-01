#include "Header.h"
#include "Player.h"
#include "HomingBullet.h"
#include "MachineGun.h"
#include "Cannon.h"
#include "MissileTurret.h"
#include "Torpedo.h"
#include "EnemyManager.h"

Player::Player()
{
	team = Team::Ally;

	spr.LoadAll(L"Assets/Sprites/Unit/Player/Ship");
	pos.y = -400;

	SetAbility(100, 300);
	SetCollider(-50, -100, 50, 100, L"ally");
	nowScene->obm.AddObject(machineGun = new MachineGun(this, D3DXVECTOR2(0, 26)));
	nowScene->obm.AddObject(cannon = new Cannon(this, D3DXVECTOR2(0, -25)));
	nowScene->obm.AddObject(turret = new MissileTurret(this, D3DXVECTOR2(2, 26)));

	
}

void Player::Update(float deltaTime)
{
	CameraControll();

	Move(deltaTime);
	SetWeaponPos();
	ShootControll();
	FirstSkillControll(deltaTime);
	SecondSkillControll(deltaTime);

	if (Input::GetInstance().KeyPress('G'))
		ability.hp -= 10 * deltaTime;

	spr.Update(deltaTime);
}

void Player::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Unit::Render();
}

bool Player::Move(float deltaTime)
{
	D3DXVECTOR2 moveDir = { 0, 0 };

	if (ability.speed < 300)
		ability.speed += 150 * deltaTime;

	if (Input::GetInstance().KeyPress(VK_DOWN))
	{
		if (ability.speed > 100)
			ability.speed -= 200 * deltaTime;
	}
	if (Input::GetInstance().KeyPress(VK_RIGHT))
		moveDir.x = 1;
	if (Input::GetInstance().KeyPress(VK_LEFT))
		moveDir.x = -1;

	D3DXVec2Normalize(&moveDir, &moveDir);

	if (moveDir.x == 0) return false;

	pos += moveDir * ability.speed * deltaTime;

	return true;
}

void Player::Hit(float damage)
{
	this->hitDamage = damage;
}

void Player::SetTarget(EnemyType enemyType)
{
	float minLength = 999999.0f;

	if (nowScene->enemyManager.allEnemys.size() <= 0)
	{
		target = NULL;
		return;
	}

	if (enemyType == EnemyType::None)
	{
		for (auto& enemy : nowScene->enemyManager.allEnemys)
		{
			D3DXVECTOR2 distance = enemy->pos - pos;
			float length = D3DXVec2Length(&distance);

			if (length < minLength)
			{
				minLength = length;
				target = enemy;
			}
		}
	}

	if (enemyType == EnemyType::FloatingEnemy)
	{
		if (nowScene->enemyManager.floatingEnemys.size() <= 0)
		{
			target = NULL;
			return;
		}

		for (auto& enemy : nowScene->enemyManager.floatingEnemys)
		{
			D3DXVECTOR2 distance = enemy->pos - pos;
			float length = D3DXVec2Length(&distance);

			if (length < minLength)
			{
				minLength = length;
				target = enemy;
			}
		}
	}

	if (enemyType == EnemyType::FlyingEnemy)
	{
		if (nowScene->enemyManager.flyingEnemys.size() <= 0)
		{
			target = NULL;
			return;
		}

		for (auto& enemy : nowScene->enemyManager.flyingEnemys)
		{
			D3DXVECTOR2 distance = enemy->pos - pos;
			float length = D3DXVec2Length(&distance);

			if (length < minLength)
			{
				minLength = length;
				target = enemy;
			}
		}
	}
}

void Player::SetWeaponPos()
{
	machineGun->pos = pos + machineGun->offset;
	cannon->pos = pos + cannon->offset;
	turret->pos = pos + turret->offset;
}

void Player::CameraControll()
{
	if (pos.x > -300 && pos.x < 300)
		Camera::GetInstance().destCameraPos.x = pos.x;


	if (Input::GetInstance().KeyDown(VK_TAB))
	{
		zoom = !zoom;

		(zoom) ? Camera::GetInstance().divideProj = 1.0f : Camera::GetInstance().divideProj = 1.5f;

		Camera::GetInstance().Init();
	}
}

void Player::ShootControll()
{
	if (Input::GetInstance().KeyPress('Q'))
	{
		SetTarget(EnemyType::None);
		machineGun->Shoot();
	}

	if (Input::GetInstance().KeyDown('W'))
	{
		SetTarget(EnemyType::None);
		cannon->Shoot();
	}

	if (Input::GetInstance().KeyDown('E'))
	{
		SetTarget(EnemyType::FloatingEnemy);

		if (target)
			nowScene->obm.AddObject(new Torpedo(pos, target, 5));
	}

	if (Input::GetInstance().KeyDown('R'))
	{
		SetTarget(EnemyType::FlyingEnemy);

		if(target)
			turret->Shoot();
	}

}

void Player::FirstSkillControll(float deltaTime)
{
	if (Input::GetInstance().KeyDown('A'))
	{
		if (!skill1 && skill1CoolTime <= 0.0f)
		{
			skill1Timer = 5.0f;
			machineGun->shootInterval /= 4;
			skill1 = true;
		}
	}


	if (skill1)
	{
		spr.color.g = spr.color.b = 0.0f;
		skill1Timer -= deltaTime;

		if (skill1Timer <= 0.0f)
		{
			spr.color.g = spr.color.b = 1.0f;
			machineGun->shootInterval *= 4;
			skill1 = false;
			skill1CoolTime = 5.0f;
		}
	}

	if (skill1CoolTime > 0.0)
		skill1CoolTime -= deltaTime;
}

void Player::SecondSkillControll(float deltaTime)
{
	if (Input::GetInstance().KeyDown('S'))
	{
		if (!skill2)
		{
			auto lambda = []{ nowScene->obm.AddObject(new Effect(L"AirBoom", D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 0.05f, 0)); };

			nowScene->obm.AddObject(new Effect(L"AirSupport", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 0.1f, 0, lambda));
			skill2 = true;
		}
	}


	if (skill2)
	{
		skill2CoolTime -= deltaTime;

		if (skill2CoolTime <= 0.0f)
		{
			skill2 = false;
			skill2CoolTime = 10.0f;
		}
	}
}
