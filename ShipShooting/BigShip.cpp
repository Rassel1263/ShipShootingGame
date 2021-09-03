#include "Header.h"
#include "BigShip.h"
#include "Effect.h"
#include "HitBox.h"
#include "BossBullet.h"
#include "BossIntro.h"

BigShip::BigShip(D3DXVECTOR2 pos) : FloatingEnemy(pos)
{
	type = EnemyType::FloatingEnemy;

	spr.LoadAll(L"Assets/Sprites/Unit/Boss/boss1.png");

	SetCollider(-900, -100, 900, 100, L"enemy");
	SetAbility(1000, 0);

	cannon.LoadAll(L"Assets/Sprites/Unit/Boss/Weapon/cannon.png");
	cannonInfo.resize(4);

	cannonInfo[0].pos = pos + D3DXVECTOR2(-105, -30);
	cannonInfo[1].pos = pos + D3DXVECTOR2(255, -30);
	cannonInfo[2].pos = pos + D3DXVECTOR2(-105, 65);
	cannonInfo[3].pos = pos + D3DXVECTOR2(255, 65);


	turret.LoadAll(L"Assets/Sprites/Unit/Boss/Weapon/turret.png");
	turretInfo.resize(2);

	turretInfo[0].pos = pos + D3DXVECTOR2(-370, 10);
	turretInfo[1].pos = pos + D3DXVECTOR2(510, 10);

	machinegun.LoadAll(L"Assets/Sprites/Unit/Boss/Weapon/machinegun.png");
	machinegunInfo.resize(4);
	
	machinegunInfo[0].pos = pos + D3DXVECTOR2(32, -85);
	machinegunInfo[1].pos = pos + D3DXVECTOR2(117, -85);
	machinegunInfo[2].pos = pos + D3DXVECTOR2(32, 104);
	machinegunInfo[3].pos = pos + D3DXVECTOR2(115, 104);

	nowScene->obm.AddObject(new BossIntro(intro));

	restTime = 1.0f;
}

void BigShip::Update(float deltaTime)
{
	if (Intro(deltaTime)) return;

	UpdatePattern(deltaTime);

	WeaponRotate(cannonInfo);
	WeaponRotate(turretInfo);
	WeaponRotate(machinegunInfo);

	CEnemy::Update(deltaTime);
}

void BigShip::Render()
{
	CEnemy::Render();

	WeaponRender(cannon, cannonInfo);
	WeaponRender(turret, turretInfo);
	WeaponRender(machinegun, machinegunInfo);
}

void BigShip::ChoosePattern()
{
	pattern = nowScene->GetRandomNumber(1, 3);
	shootInterval = 0.0f;
	cannonIndex = 0;

	if (pattern == 1)
	{
		attackTime = 4.0f;
		attackSpeed = 1.0f;
	} 
	else if (pattern == 2)
	{
		attackTime = 3.0f;
		attackSpeed = 0.5f;
	}
	else if (pattern == 3)
	{
		attackTime = 3.0f;
		attackSpeed = 0.3f;
	}
}

void BigShip::UpdatePattern(float deltaTime)
{
	bool endPattern = false;

	if (pattern == 1)
		endPattern = Pattern1(deltaTime);
	else if (pattern == 2)
		endPattern = Pattern2(deltaTime);
	else if (pattern == 3)
		endPattern = Pattern3(deltaTime);

	if (!endPattern)
	{
		restTimer += deltaTime;

		if (restTimer >= restTime)
		{
			restTimer = 0.0f;
			attackTimer = 0.0f;

			ChoosePattern();
		}
	}
	else
		attackTimer += deltaTime;
}

void BigShip::WeaponPos()
{
	cannonInfo[0].pos = pos + D3DXVECTOR2(-105, -30);
	cannonInfo[1].pos = pos + D3DXVECTOR2(255, -30);
	cannonInfo[2].pos = pos + D3DXVECTOR2(-105, 65);
	cannonInfo[3].pos = pos + D3DXVECTOR2(255, 65);

	turretInfo[0].pos = pos + D3DXVECTOR2(-370, 10);
	turretInfo[1].pos = pos + D3DXVECTOR2(510, 10);

	machinegunInfo[0].pos = pos + D3DXVECTOR2(32, -85);
	machinegunInfo[1].pos = pos + D3DXVECTOR2(117, -85);
	machinegunInfo[2].pos = pos + D3DXVECTOR2(32, 104);
	machinegunInfo[3].pos = pos + D3DXVECTOR2(115, 104);
}

void BigShip::WeaponRender(Sprite weapon, std::vector<RenderInfo> weaponInfo)
{

	int size = weaponInfo.size();
	for (int i = 0; i < size; ++i)
		weapon.Render(weaponInfo[i]);
}

void BigShip::WeaponRotate(std::vector<RenderInfo>& weaponInfo)
{
	for (auto& ri : weaponInfo)
	{
		float angle = GetAngleToTarget(ri.pos);

		ri.rotate = D3DXToDegree(-angle) + 90;
	}
}

float BigShip::GetAngleToTarget(D3DXVECTOR2 targetPos)
{
	D3DXVECTOR2 distance = nowScene->player->pos - targetPos;
	D3DXVec2Normalize(&distance, &distance);
	return atan2(distance.y, distance.x);
}

bool BigShip::Intro(float deltaTime)
{
	if (pos.y > 250)
	{
		pos.y -= deltaTime * 100;
		WeaponPos();
	}
	else
	{
		intro = false;
		return false;
	}


	return true;
}

bool BigShip::Pattern1(float deltaTime)
{
	shootInterval += deltaTime;

	if (shootInterval >= attackSpeed)
	{
		shootInterval = 0.0f;

		float angle = GetAngleToTarget(cannonInfo[cannonIndex].pos);

		D3DXVECTOR2 pos = nowScene->player->pos;
		D3DXVECTOR2 fixpos = cannonInfo[cannonIndex].pos + D3DXVECTOR2(cosf(angle), sinf(angle)) * 13;
		nowScene->obm.AddObject(new Effect(L"CannonShot", fixpos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.0f), 0.05f, cannonInfo[cannonIndex].rotate));

		auto lambda = [=]
		{
			nowScene->obm.AddObject(new Effect(L"ECannon", pos, D3DXVECTOR2(2, 2), D3DXVECTOR2(0.5, 0.5), 0.05f, 0));
			nowScene->obm.AddObject(new HitBox(pos, -50, -50, 50, 50, 10, 0.1f));
		};

		nowScene->obm.AddObject(new Effect(L"circle.png", pos, D3DXVECTOR2(1, 1), 0, 1.0f, true, 0, lambda));
		cannonIndex++;
	}

	if (attackTimer >= attackTime)
		return false;

	return true;
}

bool BigShip::Pattern2(float deltaTime)
{
	shootInterval += deltaTime;


	if (shootInterval >= attackSpeed)
	{
		shootInterval = 0.0f;

		float angle = GetAngleToTarget(turretInfo[cannonIndex].pos);

		D3DXVECTOR2 fixPos = turretInfo[cannonIndex].pos + D3DXVECTOR2(cosf(angle), sinf(angle)) * 20;
		nowScene->obm.AddObject(new Effect(L"CannonShot", fixPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.0f), 0.05f, cannonInfo[cannonIndex].rotate));
		nowScene->obm.AddObject(new BossBullet(fixPos, D3DXToDegree(angle), 0.5f, 1.0f, 10));
		cannonIndex++;

		if (cannonIndex > 1)
			cannonIndex = 0;
	}


	if (attackTimer >= attackTime)
		return false;

	return true;
}

bool BigShip::Pattern3(float deltatime)
{
	shootInterval += deltatime;

	if (shootInterval >= attackSpeed)
	{
		shootInterval = 0.0f;

		for (int i = 0; i < 4; ++i)
		{
			float angle = GetAngleToTarget(machinegunInfo[i].pos);

			D3DXVECTOR2 fixPos = machinegunInfo[i].pos + D3DXVECTOR2(cosf(angle), sinf(angle)) * 20;
			nowScene->obm.AddObject(new Effect(L"CannonShot", fixPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.0f), 0.05f, machinegunInfo[i].rotate));
			nowScene->obm.AddObject(new BossBullet(fixPos, D3DXToDegree(angle), 10, BossBullet::Type::Machinegun));
		}
	}


	if (attackTimer >= attackTime)
		return false;

	return true;
}
