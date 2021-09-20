#include "DXUT.h"
#include "HomingBullet.h"

HomingBullet::HomingBullet(D3DXVECTOR2 pos, Unit* target, BulletType type, std::wstring tag, float damage, float angle, float startTime)
	: CBullet(pos, target, tag, damage)
{
	this->pos = pos;
	this->type = type;

	this->startTime = startTime = 0.5f;
	turnSpeed = D3DXToRadian(10);

	if (target->team == Team::Enemy)
	{
		if (type == BulletType::Torpedo)
		{
			spr.LoadAll(L"Assets/Sprites/Bullet/Torpedo/", 0.05f, false);
		}

		if (type == BulletType::Missile)
		{
			spr.LoadAll(L"Assets/Sprites/Bullet/EnemyMissile", 0.05f, false);
		}

		this->angle = D3DXToRadian(angle);
		ri.rotate = angle;
	}

	if (target->team == Team::Ally)
	{
		spr.LoadAll(L"Assets/Sprites/Bullet/");
	}

}

void HomingBullet::Update(float deltaTime)
{
}

void HomingBullet::Render()
{
}

void HomingBullet::CreateEffect()
{
}

void HomingBullet::HomingSystem()
{
}
