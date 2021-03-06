#include "Header.h"
#include "HomingBullet.h"
#include "Effect.h"

HomingBullet::HomingBullet(D3DXVECTOR2 pos, Unit* target, float damage, float angle, float startTime) : CBullet(pos, target, damage)
{
	type = BulletType::Missile;
	this->pos = pos;

	if (target->team == Team::Enemy)
		spr.LoadAll(L"Assets/Sprites/Unit/Bullet/Missile");
	else if (target->team == Team::Ally)
		spr.LoadAll(L"Assets/Sprites/Unit/Bullet/Missile2.png");

	turnSpeed = D3DXToRadian(10);
	this->startTime = startTime;

	this->angle = D3DXToRadian(angle);
	ri.rotate = -angle;

	SetCollider(-10, -10, 10, 10);

	layer = 6;
}

void HomingBullet::Update(float deltaTime)
{
	if (team  == L"ally")
		HomingSystem(deltaTime);

	pos += D3DXVECTOR2(cos(angle), sinf(angle)) * 300 * deltaTime;

	CBullet::Update(deltaTime);
}

void HomingBullet::Render()
{
	CBullet::Render();
}


void HomingBullet::CreateEffect()
{
	nowScene->obm.AddObject(new Effect(L"Missile", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), 0.05f, 0));
}

void HomingBullet::HomingSystem(float deltaTime)
{
	if (target->destroy)
		homing = false;

	if (!homing) return;

	if (startTime < 0.0f)
	{
		startTime -= deltaTime;
	}
	else
	{
		D3DXVECTOR2 distance = target->pos - pos;
		float targetAngle = atan2(distance.y, distance.x);
		float diff = targetAngle - angle;

		turnTime += deltaTime;

		if (turnTime >= 0.05f)
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


			turnTime = 0.0f;
		}

		ri.rotate = D3DXToDegree(-angle);
	}
}
