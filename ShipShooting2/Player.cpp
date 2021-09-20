#include "DXUT.h"
#include "Player.h"

Player::Player()
{
	ability.SetAbility(100, 100);

	hitTime = 1.0f;

	// ¹«±âµé¤©¤©¤©¤©
	weapons.push_back(new MachineGun(this));
	weapons.push_back(new NavalGun(this));
	weapons.push_back(new TorpedoLauncher(this));
	weapons.push_back(new MissileTurret(this));

	Resize(24);

	for (int i = 0; i < 24; ++i)
		GetSprite(i).LoadAll(L"a");
		//GetSprite(i).LoadAll(L"Assets/Sprites/player/move/" + std::to_wstring(i));

	nowScene->obm.AddObject(new PlayerUI(this));
}

void Player::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown('G'))
		Hit(5);

	Move(deltaTime);
	CameraControll();
	WeaponControll(deltaTime);

	if (Input::GetInstance().KeyDown('S'))
	{
		for (int i = 0; i < 24; ++i)
			GetSprite(i).LoadAll(L"Assets/Sprites/player/move/" + std::to_wstring(i));
	}

	Unit::Update(deltaTime);
}

void Player::Render()
{
	Unit::Render();
}

bool Player::Move(float deltaTime)
{
	if (Input::GetInstance().KeyDown(VK_UP))
	{
		if (speedLevel < 4)
			speedLevel++;
	}

	if (Input::GetInstance().KeyDown(VK_DOWN))
	{
		if (speedLevel > 1)
			speedLevel--;
	}

	if (Input::GetInstance().KeyPress(VK_RIGHT))
	{
		curRotate += deltaTime * 40 * 2.5f;
		ri.rotate += deltaTime * 40;
	}

	if (Input::GetInstance().KeyUp(VK_RIGHT))
		rotateSpd = 0;

	if (Input::GetInstance().KeyPress(VK_LEFT))
	{
		curRotate -= deltaTime * 40 * 2.5f;
		ri.rotate -= deltaTime * 40;
	}
	 
	if (Input::GetInstance().KeyUp(VK_LEFT))
		rotateSpd = 0;


	/*if (nowScene->spawnBoss)
	{*/
		if (curRotate > 360)
			curRotate = 0;

		if (curRotate < 0)
			curRotate = 360;
	/*}
	else
	{
		if (curRotate < 270)
			curRotate = 270;

		if (curRotate > 450)
			curRotate = 450;
	}*/

	/*if (pos.x < -1000)
		curRotate += (360 - curRotate) * 0.1f;*/

	ability.speed = speedLevel * 50.0f;
	curRadian = D3DXToRadian(-curRotate + 90);


	pos += D3DXVECTOR2(cosf(curRadian), sinf(curRadian)) * ability.speed * deltaTime;
	SetAni(curRotate);

	return true;
}

void Player::SetTarget(EnemyType enemyType)
{
	float minLength = INT_MAX;

	if (nowScene->enemyManager.allEnemys.size() <= 0)
	{
		target = NULL;
		return;
	}

	if (enemyType == EnemyType::None)
	{
		for (auto& enemy : nowScene->enemyManager.allEnemys)
		{
			D3DXVECTOR2 distance = enemy->pos - pos;
			float length = D3DXVec2Length(&distance);

			if (length < minLength)
			{
				minLength = length;
				target = enemy;
			}
		}
	}

	if (enemyType == EnemyType::FloatingEnemy)
	{
		for (auto& enemy : nowScene->enemyManager.floatingEnemys)
		{
			D3DXVECTOR2 distance = enemy->pos - pos;
			float length = D3DXVec2Length(&distance);

			if (length < minLength)
			{
				minLength = length;
				target = enemy;
			}
		}
	}
}

void Player::CameraControll()
{
	if (pos.x > -960 && pos.x < 960)
		Camera::GetInstance().destCameraPos.x = pos.x;

	Camera::GetInstance().destCameraPos.y = pos.y + 300;
}

void Player::WeaponControll(float deltaTime)
{
	if (Input::GetInstance().KeyPress('Q'))
	{
		SetTarget(EnemyType::None);
		weapons[0]->Shoot();
	}

	if (Input::GetInstance().KeyDown('W'))
	{
		SetTarget(EnemyType::None);
		weapons[1]->Shoot();
	}
	

	for (auto& weapon : weapons)
		weapon->Update(deltaTime);
}
