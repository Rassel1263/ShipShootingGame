#include "Header.h"
#include "Player.h"
#include "HomingBullet.h"
#include "MachineGun.h"
#include "Cannon.h"
#include "MissileTurret.h"
#include "Torpedo.h"
#include "TorpedoLauncher.h"
#include "EnemyManager.h"
#include "YouDie.h"
#include "HitBox.h"
#include "Item.h"

Player::Player()
{
	team = Team::Ally;

	spr.LoadAll(L"Assets/Sprites/Unit/Player/Ship");
	pos.y = -400;

	SetAbility(100, 300);
	SetCollider(-50, -100, 50, 100, L"ally");
	nowScene->obm.AddObject(machineGun = new MachineGun(this, D3DXVECTOR2(0, 38)));
	nowScene->obm.AddObject(cannon = new Cannon(this, D3DXVECTOR2(0, -37)));
	nowScene->obm.AddObject(turret = new MissileTurret(this, D3DXVECTOR2(2, 35)));
	nowScene->obm.AddObject(torpedLauncher = new TorpedoLauncher(this));

	MiniMap::GetInstance().AddMiniObject(MINITAG::PLAYER, &pos, this);

	hitTime = 1.0f;
	skill2CoolTime = 0.0f;

	maxSpeed = 300;
	minSpeed = 100;
}

void Player::Update(float deltaTime)
{
	if (ability.hp <= 0) return;
	if (stop) return;

	CameraControll();
	Move(deltaTime);

	SetWeaponPos();
	ShootControll();
	FirstSkillControll(deltaTime);
	SecondSkillControll(deltaTime);
	UpdateEffect(deltaTime);

	if (uiTime > 0.0f)
		uiTime -= deltaTime;

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

void Player::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Unit::Render();
}

bool Player::Move(float deltaTime)
{
	D3DXVECTOR2 moveDir = { 0, 0 };

	if (ability.speed < maxSpeed)
		ability.speed += 150 * deltaTime;

	if (Input::GetInstance().KeyPress(VK_DOWN))
	{
		if (ability.speed > minSpeed)
			ability.speed -= 200 * deltaTime;
	}
	if (Input::GetInstance().KeyPress(VK_RIGHT))
	{
		moveDir.x = 1;
	}
	if (Input::GetInstance().KeyPress(VK_LEFT))
	{
		moveDir.x = -1;
	}

	D3DXVec2Normalize(&moveDir, &moveDir);

	if (moveDir.x == 0) return false;

	pos += moveDir * ability.speed * deltaTime;

	return true;
}

void Player::Hit(float damage)
{
	if (god || invincible) return;
	if (bHit) return;

	bHit = true;
	this->ability.hp -= damage;
	nowScene->obm.AddObject(new Effect(L"ouch.png", D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 1), 0, 1.0f, false));
	Camera::GetInstance().cameraQuaken = { 10, 10 };

	if (ability.hp <= 0)
		nowScene->obm.AddObject(new YouDie());
}

void Player::OnCollision(Collider& coli)
{
	if (coli.tag == L"enemybullet")
	{
		Hit(static_cast<CBullet*>(coli.obj)->damage);
	}
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
			torpedLauncher->Shoot();
	}

	if (Input::GetInstance().KeyDown('R'))
	{
		SetTarget(EnemyType::FlyingEnemy);

		if (target)
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
		else if (skill1CoolTime > 0.0f)
			SpawnUI();
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
		if (skill2CoolTime <= 0.0f)
		{
			auto lambda = []
			{
				nowScene->obm.AddObject(new Effect(L"AirBoom", D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 0.05f, 0));
				for (auto& enemy : nowScene->enemyManager.allEnemys)
					enemy->Hit(100);
			};

			nowScene->obm.AddObject(new Effect(L"AirSupport", D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 0.1f, 0, lambda));
			skill2CoolTime = 10.0f;
		}
		else if (skill2CoolTime > 0.0f)
			SpawnUI();
	}

	if (skill2CoolTime > 0.0)
		skill2CoolTime -= deltaTime;

}

void Player::UpdateEffect(float deltaTime)
{
	if (speedUp)
	{
		speedUpTime += deltaTime;

		if (speedUpTime >= 5.0f)
		{
			speedUp = false;
			speedUpTime = 0.0f;
			ability.speed = 300;
			maxSpeed = 300;
		}
	}


	if (invincible)
	{
		invincibleTime += deltaTime;

		if (invincibleTime >= 2.0f)
		{
			invincible = false;
			invincibleTime = 0.0f;
		}
	}

	if (speedDown)
	{
		speedDownTime += deltaTime;
		ability.speed = prevSpeed / 2;

		if (ability.speed < minSpeed)
			ability.speed = minSpeed;

		if (speedDownTime >= 2.0f)
		{
			speedDown = false;
			speedDownTime = 0.0f;
		}
	}
}

void Player::GetItemEffective(int index)
{
	switch (index)
	{
	case 0:
		machineGun->bulletAmount += 30;
		break;
	case 1:
		torpedLauncher->bulletAmount += 5;

		if (torpedLauncher->bulletAmount >= torpedLauncher->bulletMaxAmount)
			torpedLauncher->bulletAmount = torpedLauncher->bulletMaxAmount;
		break;
	case 2:
		turret->bulletAmount += 3;

		if (turret->bulletAmount >= turret->bulletMaxAmount)
			turret->bulletAmount = turret->bulletMaxAmount;
		break;
	case 3:
		maxSpeed = 500;
		speedUp = true;
		break;
	case 4:
		ability.hp += 10;
		if (ability.hp > ability.maxHp)
		{
			nowScene->AddScore(1000);
			ability.hp = ability.maxHp;
		}
		break;
	case 5:
		invincible = true;
		break;
	default:
		break;
	}
}

void Player::SpawnUI()
{
	if (uiTime <= 0.0f)
	{
		uiTime = 2.0f;
		Camera::GetInstance().cameraQuaken = { 4, 4 };
		nowScene->obm.AddObject(new Effect(L"dontSkill.png", D3DXVECTOR2(0, -445), D3DXVECTOR2(2, 2), 0, 2.0f, false));
	}
}
