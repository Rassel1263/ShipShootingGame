#include "Header.h"
#include "Torpedo.h"
#include "Effect.h"

Torpedo::Torpedo(D3DXVECTOR2 pos, Unit* target, float damage) : CBullet(pos, target, damage)
{
	this->pos = pos;
	this->type = BulletType::Torpedo;

	startTime = 0.5f;

	turnSpeed = D3DXToRadian(10);


	if (target->team == Team::Enemy)
	{
		spr.LoadAll(L"Assets/Sprites/Unit/Bullet/torpedo1.png");
		angle = D3DXToRadian(90);
		ri.rotate = 90;
	}
	
	if(target->team == Team::Ally)
	{
		spr.LoadAll(L"Assets/Sprites/Unit/Bullet/Etorpedo.png");
		angle = D3DXToRadian(270);
		ri.rotate = 90;
	}

	layer = 4;

	SetCollider(-10, -10, 10, 10);
}

void Torpedo::Update(float deltaTime)
{
	if(target->team == Team::Enemy)
		HomingSystem(deltaTime);

	pos += D3DXVECTOR2(cos(angle), sinf(angle)) * 500 * deltaTime;

	CBullet::Update(deltaTime);
}

void Torpedo::Render()
{
	CBullet::Render();
}

void Torpedo::CreateEffect()
{
	nowScene->obm.AddObject(new Effect(L"Torpedo", pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5f, 0.5f), 0.05f, 0));
}

void Torpedo::HomingSystem(float deltaTime)
{
	if (target->destroy)
		homing = false;

	if (!homing) return;

	if (startTime > 0.0f)
		startTime -= deltaTime;
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
