#include "DXUT.h"
#include "FlyingEnemy.h"

FlyingEnemy::FlyingEnemy(D3DXVECTOR2 pos) : CEnemy(pos)
{
	type = EnemyType::FlyingEnemy;
	airPos = pos.y;
	ability.SetAbility(100, 500);
	attackTime = 3.0f;
	attackTimer = 3.0f;

	Resize(24);

	for (int i = 0; i < 24; ++i)
		GetSprite(i).LoadAll(L"Assets/Sprites/enemy/type2/move/" + std::to_wstring(i));

	//GetSprite(i).LoadAll(L"aa" + std::to_wstring(i));

	CreateCollider(D3DXVECTOR2(-50, -50), D3DXVECTOR2(50, 50), L"enemy");

	shadow = new ColorShader();

	layer = 7;
}

void FlyingEnemy::Update(float deltaTime)
{
	attackTimer += deltaTime;

	if(setAirPos)
		pos.y = airPos;

	CEnemy::Update(deltaTime);
}

void FlyingEnemy::Render()
{
	shadowRI.pos = D3DXVECTOR2(pos.x, airPos - 150);
	shadowRI.scale = D3DXVECTOR2((airPos - 150) / pos.y, (airPos - 150) / pos.y);
	
	shadow->Render(shadow, GetNowSprite(), shadowRI, D3DXVECTOR4(0, 0, 0, 0.5f));

	CEnemy::Render();
}

void FlyingEnemy::Destroy()
{
	nowScene->AddScore(nowScene->GetRandomNumber(1000, 2000));
	nowScene->obm.AddObject(new Item(pos, nowScene->GetRandomNumber(0, 5)));
	nowScene->obm.AddObject(new Effect(L"onexplode", pos, D3DXVECTOR2(0.4, 0.4), D3DXVECTOR2(0.5, 0.5), 1, true, 0.05f));
	SoundManager::GetInstance().Play(L"explo");
	nowScene->player->kills++;

	CEnemy::Destroy();
}

bool FlyingEnemy::Move(float deltaTime)
{
	float targetAngle = D3DXToRadian(nowScene->GetAngleFromTarget(D3DXVECTOR2(pos.x, airPos), target->pos));  // -90 ~ 270 
	float diff = targetAngle - curRadian;

	if (attackTimer >= attackTime)
		turnTime += deltaTime;

	if (turnTime >= 0.01f)
	{
		if (diff > D3DX_PI)
			diff -= D3DX_PI * 2;
		else if (diff < -D3DX_PI)
			diff += D3DX_PI * 2;

		if (diff > turnSpeed)
			curRadian += turnSpeed;
		else if (diff < -turnSpeed)
			curRadian -= turnSpeed;
		else
		{
			Attack(deltaTime);
			curRadian = targetAngle;
		}

		turnTime = 0.0f;
	}

	SetAni(D3DXToDegree(-curRadian) + 450);

	pos.x += cosf(curRadian) * ability.speed * deltaTime;
	airPos += sinf(curRadian) * ability.speed * deltaTime;

	return true;
}

void FlyingEnemy::Attack(float deltaTime)
{
	D3DXVECTOR2 distance = nowScene->player->pos - pos;

	if (D3DXVec2Length(&distance) <= 400)
	{
		if (attackTimer >= attackTime)
		{
			int num = nowScene->GetRandomNumber(3, 4);
			for (int i = 0; i < num; ++i)
				nowScene->obm.AddObject(new HomingBullet(pos, target, CBullet::BulletType::Missile, L"enemy", 10,
					D3DXToDegree(-curRadian) + 90 + nowScene->GetRandomNumber(-45, 45), 0.0f, 400));

			ability.speed = 500;
			attackTimer = 0.0f;
		}
	}
}
