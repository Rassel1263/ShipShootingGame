#include "Header.h"
#include "BigPlane.h"
#include "Effect.h"
#include "HitBox.h"
#include "BossBullet.h"
#include "BossIntro.h"
#include "CalcPage.h"
#include "Item.h"

BigPlane::BigPlane(D3DXVECTOR2 pos) : FlyingEnemy(pos)
{
	type = EnemyType::FlyingEnemy;

	spr.LoadAll(L"Assets/Sprites/Unit/Boss/boss1.png");

	SetCollider(-900, -100, 900, 100, L"enemy");
	SetAbility(100, 0);

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

	for (auto& enemy : nowScene->enemyManager.allEnemys)
	{
		if (enemy != this)
			enemy->Hit(100);
	}

	outroTime = 10.0f;
	effectTime = 1.0f;
	restTime = 1.0f;

	layer = 6;
}

void BigPlane::Update(float deltaTime)
{
	if (Intro(deltaTime)) return;
	if (Transform(deltaTime)) return;
	if (Outro(deltaTime)) return;


	UpdatePattern(deltaTime);

	if (!transform)
	{
		WeaponRotate(turretInfo);
		WeaponRotate(machinegunInfo);
	}
	WeaponRotate(cannonInfo);


	CEnemy::Update(deltaTime);
}

void BigPlane::Render()
{
	CEnemy::Render();

	WeaponRender(machinegun, machinegunInfo);
	WeaponRender(turret, turretInfo);

	WeaponRender(cannon, cannonInfo);

}

void BigPlane::ChoosePattern()
{
	while (pattern == prevPattern)
		pattern = nowScene->GetRandomNumber(1, 3);

	prevPattern = pattern;
	shootInterval = 0.0f;
	cannonIndex = 0;
	turret.scene = 0;

	if (!transform)
	{
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
	else
	{
		if (pattern == 1)
		{
			attackTime = 5.0f;
			attackSpeed = 0.5f;
		}
		else if (pattern == 2)
		{
			attackTime = 3.5f;
			attackSpeed = 0.5f;
		}
		else if (pattern == 3)
		{
			attackTime = 3.0f;
			attackSpeed = 0.3f;
		}
	}
}

void BigPlane::UpdatePattern(float deltaTime)
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

void BigPlane::WeaponPos(int phase)
{
	if (phase == 1)
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
	else
	{
		cannonInfo[0].pos = pos + D3DXVECTOR2(-140, 25);
		cannonInfo[1].pos = pos + D3DXVECTOR2(140, 25);

		turretInfo[0].pos = pos + D3DXVECTOR2(-110, -310);
		turretInfo[1].pos = pos + D3DXVECTOR2(-40, -310);
		turretInfo[2].pos = pos + D3DXVECTOR2(40, -310);
		turretInfo[3].pos = pos + D3DXVECTOR2(110, -310);
		turretInfo[4].pos = pos + D3DXVECTOR2(-110, -290);
		turretInfo[5].pos = pos + D3DXVECTOR2(-40, -290);
		turretInfo[6].pos = pos + D3DXVECTOR2(40, -290);
		turretInfo[7].pos = pos + D3DXVECTOR2(110, -290);

		machinegunInfo[0].pos = pos + D3DXVECTOR2(-120, -380);
		machinegunInfo[1].pos = pos + D3DXVECTOR2(-50, -380);
		machinegunInfo[2].pos = pos + D3DXVECTOR2(50, -380);
		machinegunInfo[3].pos = pos + D3DXVECTOR2(120, -380);
	}
}

void BigPlane::WeaponRender(Sprite weapon, std::vector<RenderInfo> weaponInfo)
{

	int size = weaponInfo.size();
	for (int i = 0; i < size; ++i)
	{
		weapon.color.a = spr.color.a;
		weapon.Render(weaponInfo[i]);
	}
}

void BigPlane::WeaponRotate(std::vector<RenderInfo>& weaponInfo, bool reset)
{
	for (auto& ri : weaponInfo)
	{
		float angle = GetAngleToTarget(ri.pos);

		(reset) ? ri.rotate = 0 : ri.rotate = D3DXToDegree(-angle) + 90;
	}
}

float BigPlane::GetAngleToTarget(D3DXVECTOR2 targetPos)
{
	D3DXVECTOR2 distance = nowScene->player->pos - targetPos;
	D3DXVec2Normalize(&distance, &distance);
	return atan2(distance.y, distance.x);
}

bool BigPlane::Intro(float deltaTime)
{
	if (pos.y > 250 && intro)
	{
		pos.y -= deltaTime * 100;
		WeaponPos(1);
	}
	else
	{
		intro = false;
		return false;
	}

	return true;
}

bool BigPlane::Transform(float deltaTime)
{
	if (ability.hp <= 0 && !transform)
	{
		bHit = false;

		spr.color.a += deltaTime * destColor;

		if (pos.y < 600 && destColor == 1.0f)
		{
			WeaponPos(2);
			pos.y += deltaTime * 200;
		}

		if (spr.color.a < 0.0f)
		{
			spr.LoadAll(L"Assets/Sprites/Unit/Boss/boss2.png");

			cannon.LoadAll(L"Assets/Sprites/Unit/Boss/Weapon/cannon2.png");
			turret.LoadAll(L"Assets/Sprites/Unit/Boss/Weapon/turret2", 0.01f, false);
			machinegun.LoadAll(L"Assets/Sprites/Unit/Boss/Weapon/machinegun2.png");

			cannonInfo.resize(2);
			turretInfo.resize(8);
			machinegunInfo.resize(4);


			WeaponRotate(turretInfo, true);
			WeaponRotate(machinegunInfo, true);
			WeaponRotate(cannonInfo, true);

			destColor = 1.0f;
		}

		Camera::GetInstance().cameraQuaken = { 4, 4 };

		if (spr.color.a > 1.0f)
		{
			ability.hp = 100;
			transform = true;
		}

		return true;
	}

	return false;
}

bool BigPlane::Outro(float deltaTime)
{
	if (ability.hp <= 0)
	{
		nowScene->player->stop = true;

		bHit = false;
		nowScene->stopTime = true;


		outroTime -= deltaTime;
		effectTimer += deltaTime;

		if (outroTime <= 0.0f)
		{
			Camera::GetInstance().destCameraPos = { nowScene->player->pos.x, 0.0f };
			spr.color.a -= deltaTime;

			if (spr.color.a < 0.0f)
			{
				nowScene->obm.AddObject(new CalcPage());
				destroy = true;
			}
		}
		else
		{
			Camera::GetInstance().destCameraPos = pos;
			if (effectTimer >= effectTime)
			{
				for (int i = 0; i < effectAmount; ++i)
					nowScene->obm.AddObject(new Effect(L"ECannon", pos + D3DXVECTOR2(nowScene->GetRandomNumber(-600, 600), nowScene->GetRandomNumber(-600, 600)), D3DXVECTOR2(2, 2), D3DXVECTOR2(0.5, 0.5), 0.05f, 0));

				effectTimer = 0.0f;
				effectTime -= 0.05f;

				Camera::GetInstance().cameraQuaken = { 10 - outroTime, 10 - outroTime };

				effectAmount++;
			}
		}

		return true;
	}

	return false;
}

bool BigPlane::Pattern1(float deltaTime)
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

		if (++cannonIndex > 1)
			cannonIndex = 0;
	}

	if (attackTimer >= attackTime)
		return false;

	return true;
}

bool BigPlane::Pattern2(float deltaTime)
{
	shootInterval += deltaTime;

	turret.Update(deltaTime);

	if (shootInterval >= attackSpeed)
	{
		shootInterval = 0.0f;

		float angle = GetAngleToTarget(turretInfo[cannonIndex].pos);

		D3DXVECTOR2 fixPos = turretInfo[cannonIndex].pos + D3DXVECTOR2(-20, 0) + D3DXVECTOR2(cosf(angle), sinf(angle)) * 20;
		nowScene->obm.AddObject(new Effect(L"CannonShot", fixPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.0f), 0.05f, turretInfo[cannonIndex].rotate));

		if (transform)
		{
			for (int i = 0; i < 4; ++i)
				nowScene->obm.AddObject(new BossBullet(fixPos + D3DXVECTOR2(i * 20, 0), D3DXToDegree(angle), 0.2f, 0.5f, 10));

			cannonIndex++;
		}
		else
		{
			nowScene->obm.AddObject(new BossBullet(fixPos, D3DXToDegree(angle), 0.5f, 1.0f, 10));

			if (++cannonIndex > 1)
				cannonIndex = 0;
		}

	}


	if (attackTimer >= attackTime)
		return false;

	return true;
}

bool BigPlane::Pattern3(float deltatime)
{
	shootInterval += deltatime;

	if (shootInterval >= attackSpeed)
	{
		shootInterval = 0.0f;
		nowScene->obm.AddObject(new Item(D3DXVECTOR2(nowScene->GetRandomNumber(-500, 500), 300), 5));

		for (int i = 0; i < 4; ++i)
		{
			float angle = GetAngleToTarget(machinegunInfo[i].pos);

			D3DXVECTOR2 fixPos = machinegunInfo[i].pos + D3DXVECTOR2(cosf(angle), sinf(angle)) * 20;

			if (transform)
			{
				nowScene->obm.AddObject(new Effect(L"CannonShot", fixPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.0f), 0.05f, 180));
				nowScene->obm.AddObject(new BossBullet(fixPos, D3DXToDegree(angle) + nowScene->GetRandomNumber(-20, 20), 5, BossBullet::Type::Machinegun));
			}
			else
				nowScene->obm.AddObject(new BossBullet(fixPos, D3DXToDegree(angle), 10, BossBullet::Type::Machinegun));
		}

		if (attackTimer >= attackTime)
			return false;

		return true;
	}
}
