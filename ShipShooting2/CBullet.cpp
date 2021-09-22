#include "DXUT.h"
#include "CBullet.h"

CBullet::CBullet(D3DXVECTOR2 pos, Unit* target, std::wstring team, float damage)
{
	this->pos = pos;
	this->target = target;
	this->damage = damage;
	this->team = team;

	spr.LoadAll(L"Assets/Sprites/bullet/machinegunBullet/");
	CreateCollider(D3DXVECTOR2(-5, -5), D3DXVECTOR2(5, 5), team + L"bullet");

	layer = 5;
}

void CBullet::Update(float deltaTime)
{
	D3DXVECTOR2 asd = Camera::GetInstance().limitPos;

	std::cout << asd.x << std::endl;

	if (pos.x > Camera::GetInstance().limitPos.x || pos.x < -Camera::GetInstance().limitPos.x ||
		pos.y > Camera::GetInstance().limitPos.y || pos.y < -Camera::GetInstance().limitPos.y)
		destroy = true;

	pos += D3DXVECTOR2(cosf(angle), sinf(angle)) * deltaTime * speed;

	spr.Update(deltaTime);
}

void CBullet::Render()
{
	ri.pos = pos;
	spr.Render(ri);

	Object::Render();
}

void CBullet::OnCollision(Collider& coli) 
{
	if (target)
	{
		if (coli.tag == L"obstacle")
		{
			if (static_cast<Obstacle*>(coli.obj)->type == Obstacle::ObstalceType::ROCK)
			{
				CreateEffect();
				destroy = true;
			}
		}

		if ((team == L"ally" && coli.tag == L"enemy") || (team == L"enemy" && coli.tag == L"ally"))
		{
			if (team == L"ally")
			{
				if (type == BulletType::Torpedo && static_cast<CEnemy*>(coli.obj)->type != EnemyType::FloatingEnemy) return;
				if (type == BulletType::Missile && static_cast<CEnemy*>(coli.obj)->type != EnemyType::FlyingEnemy) return;
			}

			CreateEffect();
			destroy= true;
		}
	}
}
