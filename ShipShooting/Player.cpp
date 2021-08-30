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
	spr.LoadAll(L"Assets/Sprites/Unit/Player/Ship");
	pos.y = -200;

	SetAbility(100, 300);
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

	if (Input::GetInstance().KeyDown('A'))
	{
		if (!skill1 && skill1CoolTime <= 0.0f)
		{
			skil1Timer = 5.0f;
			machineGun->shootInterval /= 4;
			skill1 = true;
		}
	}


	if (skill1)
	{
		spr.color.g = spr.color.b = 0.0f;
		skil1Timer -= deltaTime;

		if (skil1Timer <= 0.0f)
		{
			spr.color.g = spr.color.b = 1.0f;
			machineGun->shootInterval *= 4;
			skill1 = false;
			skill1CoolTime = 5.0f;
		}
	}

	if(skill1CoolTime > 0.0)
		skill1CoolTime -= deltaTime;


	spr.Update(deltaTime);
}

void Player::Render()
{
	ri.pos = pos;
	spr.Render(ri);
}

bool Player::Move(float deltaTime)
{
	D3DXVECTOR2 moveDir = { 0, 0 };

	if (ability.speed < 300)
		ability.speed += 150 * deltaTime;

	if (Input::GetInstance().KeyPress(VK_DOWN))
	{
		if (ability.speed > 200)
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

void Player::SetTarget(EnemyType enemyType)
{
	float minLength = 999999.0f;

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
		static bool toggle = false;

		toggle = !toggle;

		if (toggle)
		{
			Camera::GetInstance().divideProj = 0.9f;
		}
		else
			Camera::GetInstance().divideProj = 1.5f;


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
			nowScene->obm.AddObject(new Torpedo(pos, target));
	}

	if (Input::GetInstance().KeyDown('R'))
	{
		SetTarget(EnemyType::FlyingEnemy);
		turret->Shoot();
	}


}
