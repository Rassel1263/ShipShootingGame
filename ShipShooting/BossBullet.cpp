#include "Header.h"
#include "BossBullet.h"
#include "Effect.h"

BossBullet::BossBullet(D3DXVECTOR2 pos, float angle, float damage, Type type) : CBullet(pos, nowScene->player, damage)
{
	this->type = type;

	if (type == Type::Machinegun)
		spr.LoadAll(L"Assets/Sprites/Unit/Bullet/boss.png");
	else if (type == Type::Torpedo)
		spr.LoadAll(L"Assets/Sprites/Unit/Bullet/Etorpedo.png");
	else if (type == Type::Missile)
		spr.LoadAll(L"Assets/Sprites/Unit/Bullet/Missile2.png");

	ri.rotate = -angle;
	this->angle = D3DXToRadian(angle);

	SetCollider(-5, -5, -5, -5);

	layer = 6;
}

BossBullet::BossBullet(D3DXVECTOR2 pos, float angle, float startTime, float homingTime, float damage) : CBullet(pos, nowScene->player, damage)
{
	spr.LoadAll(L"Assets/Sprites/Unit/Bullet/Missile2.png");

	this->type = Type::Missile;
	this->homing = true;
	this->startTime = startTime;
	this->homingTime = homingTime;

	turnSpeed = D3DXToRadian(10);

	ri.rotate = -angle;
	this->angle = D3DXToRadian(angle);

	SetCollider(-5, -5, -5, -5);
}

void BossBullet::Update(float deltaTime)
{
	if (homing)
		HomingSystem(deltaTime);

	pos += D3DXVECTOR2(cos(angle), sinf(angle)) * 300 * deltaTime;

	CBullet::Update(deltaTime);
}

void BossBullet::Render()
{
	CBullet::Render();
}

void BossBullet::CreateEffect()
{
	nowScene->obm.AddObject(new Effect(L"Missile", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), 0.05f, 0));
}

void BossBullet::HomingSystem(float deltaTime)
{
	if (startTime > 0.0f)
	{
		startTime -= deltaTime;
	}
	else
	{
		if (homingTime <= 0.0f) return;

		homingTime -= deltaTime;

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
