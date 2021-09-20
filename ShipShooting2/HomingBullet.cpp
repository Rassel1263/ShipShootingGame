#include "DXUT.h"
#include "HomingBullet.h"

HomingBullet::HomingBullet(D3DXVECTOR2 pos, Unit* target, BulletType type, std::wstring team, float damage, float angle, float startTime)
	: CBullet(pos, target, team, damage)
{
	this->pos = pos;
	this->type = type;

	speed = 300;

	this->startTime = startTime;
	turnSpeed = D3DXToRadian(10);
	if (team == L"ally") homing = true;

	if (type == BulletType::Torpedo)
	{
		spr.LoadAll(L"Assets/Sprites/Bullet/Torpedo/", 0.05f);

		layer = 4;
	}

	if (type == BulletType::Missile)
	{
		if (team == L"ally")
			spr.LoadAll(L"Assets/Sprites/Bullet/PlayerMissile", 0.05f);
		else if(team == L"enemy")
			spr.LoadAll(L"Assets/Sprites/Bullet/EnemyMissile", 0.05f);

		layer = 6;
	}

	this->angle = D3DXToRadian(-angle + 90);
	ri.rotate = angle;
}

void HomingBullet::Update(float deltaTime)
{
	if (team == L"ally")
		HomingSystem(deltaTime);

	CBullet::Update(deltaTime);
}

void HomingBullet::Render()
{
	CBullet::Render();
}

void HomingBullet::CreateEffect()
{
	if (type == BulletType::Torpedo)
		nowScene->obm.AddObject(new Effect(L"Hit_Torpedo/", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
	else
		nowScene->obm.AddObject(new Effect(L"Hit_missile/", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f, -nowScene->GetAngleFromTarget(pos, target->pos) + 90));
}

void HomingBullet::HomingSystem(float deltaTime)
{
	if (!homing) return;

	if (target->destroy)
		homing = false;

	if (startTime > 0.0f)
		startTime -= deltaTime;
	else
	{
		float targetAngle = D3DXToRadian(nowScene->GetAngleFromTarget(pos, target->pos));
		float diff = targetAngle - angle;

		turnTimer += deltaTime;

		if (turnTimer >= 0.05f)
		{
			if (diff > D3DX_PI)
				diff -= D3DX_PI * 2;
			else if (diff < -D3DX_PI)
				diff += D3DX_PI * 2;

			if (diff > turnSpeed)
				angle += turnSpeed;
			else if (diff < -turnSpeed)
				angle -= turnSpeed;
			else
				angle = targetAngle;

			turnTimer = 0.0f;
		}

		ri.rotate = D3DXToDegree(-angle) + 90;
	}
}
