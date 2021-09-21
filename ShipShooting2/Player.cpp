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
		GetSprite(i).LoadAll(L"Assets/Sprites/player/move/" + std::to_wstring(i));
		//GetSprite(i).LoadAll(L"a");

	CreateCollider(D3DXVECTOR2(-100, -100), D3DXVECTOR2(100, 100), L"player");

	nowScene->obm.AddObject(new PlayerUI(this));
}

void Player::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown('G'))
		nowScene->obm.AddObject(new Item(D3DXVECTOR2(0, 400), nowScene->GetRandomNumber(0, 5)));

	Move(deltaTime);
	CameraControll();
	WeaponControll(deltaTime);
	UpdateItemEffect(deltaTime);
	FirstSkillControll(deltaTime);
	SecondSkillControll(deltaTime);

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

void Player::OnCollision(Collider& coli)
{
	if (coli.tag == L"obstacle")
	{
		auto obj = static_cast<Obstacle*>(coli.obj);

		if (obj->type == Obstacle::ObstalceType::GARBAGE)
		{
			if (!speedDown)
			{
				speedDownTime = 2.0f;
				speedDown = true;
			}
		}
	}
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

	destSpeed = speedLevel * ((speedUp) ? 100.0f : 50.0f);
	if (speedDown) destSpeed *= 0.5f;
	ability.speed += std::ceil(destSpeed - ability.speed) * 0.1f;
	
	curRadian = D3DXToRadian(-curRotate + 90);

	float prevPosY = pos.y;
	pos += D3DXVECTOR2(cosf(curRadian), sinf(curRadian)) * ability.speed* deltaTime;
	dps = pos.y - prevPosY;

	SetAni(curRotate);

	return true;
}

void Player::SetTarget(EnemyType enemyType)
{
	float minLength = INT_MAX;
	target = NULL;

	if (nowScene->enemyManager.allEnemys.size() <= 0)
		return;

	if (enemyType == EnemyType::None)
	{
		for (auto& enemy : nowScene->enemyManager.allEnemys)
		{
			if (enemy->ability.hp <= 0) 
				continue;

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
			if (enemy->ability.hp <= 0)
				continue;

			D3DXVECTOR2 distance = enemy->pos - pos;
			float length = D3DXVec2Length(&distance);

			if (length < minLength)
			{
				minLength = length;
				target = enemy;
			}
		}
	}

	if (enemyType == EnemyType::FlyingEnemy)
	{
		for (auto& enemy : nowScene->enemyManager.flyingEnemys)
		{
			if (enemy->ability.hp <= 0) continue;

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

void Player::SetItemEffective(int index)
{
	switch (index)
	{
	case 0:
		weapons[0]->bulletAmount += 30;
		if (weapons[0]->bulletAmount >= 180)
			weapons[0]->bulletAmount = 180;
		break;
	case 1:
		weapons[2]->bulletAmount += 5;
		if (weapons[2]->bulletAmount >= weapons[2]->bulletMaxAmount)
			weapons[2]->bulletAmount = weapons[2]->bulletMaxAmount;
		break;
	case 2:
		weapons[3]->bulletAmount += 3;
		if (weapons[3]->bulletAmount >= weapons[3]->bulletMaxAmount)
			weapons[3]->bulletAmount = weapons[3]->bulletMaxAmount;
		break;
	case 3:
		speedUp = true;
		speedUpTime = 5.0f;
		break;
	case 4:
		invincible = true;
		invincibleTime = 2.0f;
		break;
	case 5:
		ability.hp += 10;
		if (ability.hp > ability.maxHp)
		{
			ability.hp = ability.maxHp;
		}
		break;
	}
}

void Player::UpdateItemEffect(float deltaTime)
{
	if (speedUp)
	{
		speedUpTime -= deltaTime;

		if (speedUpTime <= 0.0f)
		{
			speedUp = false;
		}
	}

	if (speedDown)
	{
		speedDownTime -= deltaTime;

		if (speedDownTime <= 0.0f)
			speedDown = false;
	}

	if (invincible)
	{
		invincibleTime -= deltaTime;

		if (invincibleTime <= 0.0f)
		{
			invincible = false;
		}
	}
}

void Player::FirstSkillControll(float deltaTime)
{
	if (Input::GetInstance().KeyDown('A'))
	{
		if (!skill1 && skill1CoolTime <= 0.0f)
		{
			skill1Timer = 5.0f;
			weapons[0]->shootInterval /= 4;
			skill1 = true;
			nowScene->obm.AddObject(new FocusedFire());
		}
	}

	if (skill1)
	{
		skill1Timer -= deltaTime;

		if (skill1Timer <= 0.0f)
		{
			weapons[0]->shootInterval *= 4;
			skill1 = false;
			skill1Msg = false;
			skill1CoolTime = 10.0f;
		}
	}

	if (skill1CoolTime > 0.0f)
		skill1CoolTime -= deltaTime;
	else
	{
		if (!skill1Msg)
		{
			skill1Msg = true;
			nowScene->msgBox->SpawnMsgBox(L"focusedfireReady");
		}
	}
}

void Player::SecondSkillControll(float deltaTime)
{
	if (Input::GetInstance().KeyDown('S'))
	{
		if (skill2CoolTime <= 0.0f)
		{
			nowScene->obm.AddObject(new Airsupport(pos.x));

			skill2CoolTime = 20.0f;
			skill2Msg = false;
		}
	}

	if (skill2CoolTime > 0.0f)
		skill2CoolTime -= deltaTime;
	else
	{
		if (!skill2Msg)
		{
			skill2Msg = true;
			nowScene->msgBox->SpawnMsgBox(L"airstrikeReady");
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
	
	if (Input::GetInstance().KeyDown('E'))
	{
		SetTarget(EnemyType::FloatingEnemy);

		if(target)
			weapons[2]->Shoot();
	}

	if (Input::GetInstance().KeyDown('R'))
	{
		SetTarget(EnemyType::FlyingEnemy);

		if(target)
			weapons[3]->Shoot();
	}

	for (auto& weapon : weapons)
		weapon->Update(deltaTime);
}
