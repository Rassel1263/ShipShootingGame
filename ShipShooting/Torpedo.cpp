#include "Header.h"
#include "Torpedo.h"
#include "Effect.h"

Torpedo::Torpedo(D3DXVECTOR2 pos, Unit* target) : CBullet(pos, target)
{
	this->pos = pos;
	spr.LoadAll(L"Assets/Sprites/Unit/Bullet/torpedo.png");
	turnSpeed = D3DXToRadian(10);
	startTime = 0.5f;

	angle = D3DXToRadian(90);
	layer = 1;

	SetCollider(-10, -10, 10, 10);
}

void Torpedo::Update(float deltaTime)
{
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
	}


	ri.rotate = D3DXToDegree(-angle);
	pos += D3DXVECTOR2(cos(angle), sinf(angle)) * 300 * deltaTime;

	CBullet::Update(deltaTime);
}

void Torpedo::Render()
{
	CBullet::Render();
}

void Torpedo::CreateEffect()
{
	nowScene->obm.AddObject(new Effect(L"Torpedo", pos, D3DXVECTOR2(1, 1), 0.05f, 0, 1));
}
