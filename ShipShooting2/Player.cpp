#include "DXUT.h"
#include "Player.h"

Player::Player()
{
	ability.SetAbility(100, 200);

	hitTime = 3.0f;

	// ¹«±âµé¤©¤©¤©¤©
	weapons.push_back(new MachineGun(this));
	weapons.push_back(new NavalGun(this));
	weapons.push_back(new TorpedoLauncher(this));
	weapons.push_back(new MissileTurret(this));

	skill2CoolTime = 5.0f;

	Resize(24);

	for (int i = 0; i < 24; ++i)
		GetSprite(i).LoadAll(L"Assets/Sprites/player/move/" + std::to_wstring(i));
	//	GetSprite(i).LoadAll(L"a" + std::to_wstring(i));

	CreateCollider(D3DXVECTOR2(-70, -70), D3DXVECTOR2(70, 70), L"player");

	nowScene->obm.AddObject(new PlayerUI(this));
	nowScene->miniMap->AddMiniObj(MINITAG::PLAYER, &pos, this);

	blinkShader = new BlinkShader();

	limitPos = { 2000, 600 };
}

void Player::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown('G'))
		nowScene->enemyManager.SpawnEnemy(pos + D3DXVECTOR2(0, 400), EnemyType::BigPlane);

	if (Input::GetInstance().KeyDown('F'))
	{
		speedDown = true;
		speedDownTime = 2.0f;
	}

	if (ability.hp <= 0)
	{
		if (!GetNowSprite().bAnimation && !drawGameOver)
		{
			drawGameOver = true;
			nowScene->obm.AddObject(new StageFont(StageFont::Type::FAIL));
		}

		GetNowSprite().Update(Game::GetInstance().unscaleTime);
		return;
	}

	if (!stop)
	{
		Move(deltaTime);
		WeaponControll(deltaTime);
		UpdateItemEffect(deltaTime);
		FirstSkillControll(deltaTime);
		SecondSkillControll(deltaTime);
	}

	TargetUpdate(deltaTime);

	if (fallowCamera)
		CameraControll();

	if (!nowScene->stageStart)
		pos.y += 50 * Game::GetInstance().unscaleTime;

	Blink(deltaTime);
	Unit::Update(deltaTime);
}

void Player::Render()
{
	ri.pos = pos;

	if (invincible || god)
	{
		colorShader->Render(colorShader, GetNowSprite(), ri, D3DXVECTOR4(1.0f, 0.7f, 0, 0.0f), true);
	}
	else if (blink)
	{
		blinkShader->Render(blinkShader, GetNowSprite(), ri, blinkTimer, blinkTime);
	}
	else if (speedDown)
	{
		colorShader->Render(colorShader, GetNowSprite(), ri, D3DXVECTOR4(0, 0.5, 0, 0), true);
	}
	else
		GetNowSprite().Render(ri);

	Object::Render();
}

void Player::OnCollision(Collider& coli)
{

	if (coli.tag == L"obstacle")
	{
		if (invincible || god) return;
		auto obj = static_cast<Obstacle*>(coli.obj);


		if (obj->type == Obstacle::ObstalceType::MINE)
		{
			Hit(20);
			Camera::GetInstance().cameraQuaken = { 10, 10 };
		}

		if (obj->type == Obstacle::ObstalceType::ROCK)
		{
			Hit(20);
			pos = D3DXVECTOR2(pos.x, pos.y - 300);
		}

		if (!speedDown)
		{
			speedDownTime = 2.0f;
			speedDown = true;
		}
	}

	if (coli.tag == L"hitBox")
	{
		Hit(static_cast<AttackCollider*>(coli.obj)->damage);
	}

	if (coli.tag == L"enemybullet")
	{
		Hit(static_cast<CBullet*>(coli.obj)->damage);
	}
}

bool Player::Move(float deltaTime)
{
	std::cout << pos.x << "     " << pos.y << std::endl;

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
		curRotate += deltaTime * 50 * speedLevel;
	}

	if (Input::GetInstance().KeyUp(VK_RIGHT))
		rotateSpd = 0;

	if (Input::GetInstance().KeyPress(VK_LEFT))
	{
		curRotate -= deltaTime * 50 * speedLevel;
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

	destSpeed = speedLevel * ((speedUp) ? 150.0f : 75.0f);
	if (speedDown) destSpeed *= 0.5f;
	ability.speed += std::ceil(destSpeed - ability.speed) * 0.1f;

	curRadian = D3DXToRadian(-curRotate + 90);

	D3DXVECTOR2 prevPos = pos;

	pos += D3DXVECTOR2(cosf(curRadian), sinf(curRadian)) * ability.speed * deltaTime;

	if (!nowScene->spawnBoss)
	{
		dps = pos.y - prevPos.y;
		moveDistance += dps;
	}

	SetAni(curRotate);

	if (nowScene->spawnBoss)
	{
		if (pos.x > Camera::GetInstance().cameraPos.x + 1300 || pos.x < Camera::GetInstance().cameraPos.x - 1300 ||
			pos.y > Camera::GetInstance().cameraPos.y + 700 || pos.y < Camera::GetInstance().cameraPos.y - 700)
		{
			pos = prevPos;
			return false;
		}
	}
	else
	{
		if (pos.x > limitPos.x + 1 || pos.x < -limitPos.x - 1)
		{
			pos = prevPos;
			return false;
		}
	}

	return true;
}

void Player::Hit(float damage)
{
	if (hit) return;
	if (god || invincible) return;

	Camera::GetInstance().cameraQuaken = { 20, 20};
	hit = true;
	blink = true;
	this->ability.hp -= damage;
	nowScene->msgBox->SpawnMsgBox(L"Hit");
	nowScene->obm.AddObject(new Effect(L"ouch.png", D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 2, false, 1.0f));

	if (ability.hp <= 0)
	{
		GetNowSprite().LoadAll(L"Assets/Sprites/player/sink/" + std::to_wstring(renderNum), 0.05f, false);
		GetNowSprite().Reset();

		nowScene->stopTime = true;

		Camera::GetInstance().destCameraPos = { pos.x, pos.y };
		Camera::GetInstance().destDivideProj = 1.5f;

		Game::GetInstance().timeScale = 0.2f;

		bCollider = false;
		ability.hp = 0;
	}
}

void Player::Blink(float deltaTime)
{
	if (blink)
	{
		blinkTimer += deltaTime * destBlink;

		blinkTimer = std::clamp(blinkTimer, 0.0f, blinkTime);

		if (blinkTimer >= blinkTime || blinkTimer <= 0.0f)
		{
			destBlink = -destBlink;
			blinkAmount++;
		}

		if (blinkAmount > 6)
		{
			blink = false;
			destBlink = -1.0f;
			blinkAmount = 0;
			blinkTimer = 0.0f;
		}
	}
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
			if (enemy->ability.hp <= 0) continue;
			if (!CameraInCheck(enemy->pos)) continue;

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
			if (enemy->ability.hp <= 0) continue;
			if (!CameraInCheck(enemy->pos)) continue;

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
			if (!CameraInCheck(enemy->pos)) continue;

			D3DXVECTOR2 distance = enemy->pos - pos;
			float length = D3DXVec2Length(&distance);

			if (length < minLength)
			{
				minLength = length;
				target = enemy;
			}
		}
	}

	if (target)
	{
		targetRestTime = 0.75f;

		if (prevTarget != target)
		{
			prevTarget = target;
			nowScene->obm.AddObject(new Effect(L"Sniper", &target->pos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 0.1f));
		}
	}

}

void Player::TargetUpdate(float deltaTime)
{
	if (target)
	{
		targetRestTime -= deltaTime;

		if (target->pos.x > pos.x + 960 || target->pos.x < pos.x - 960 || target->destroy)
		{
			prevTarget = target;
			target = NULL;
		}

		if (targetRestTime <= 0.0f)
			target = NULL;

	}
}

bool Player::CameraInCheck(D3DXVECTOR2 pos)
{
	if (pos.x < Camera::GetInstance().cameraPos.x + 960 && pos.x > Camera::GetInstance().cameraPos.x - 960 &&
		pos.y < Camera::GetInstance().cameraPos.y + 540 && pos.y > Camera::GetInstance().cameraPos.y - 540)
		return true;

	return false;
}

void Player::SetItemEffective(int index)
{
	switch (index)
	{
	case 0:
		SoundManager::GetInstance().Play(L"realod");
		weapons[0]->bulletAmount += 30;
		if (weapons[0]->bulletAmount >= 180)
			weapons[0]->bulletAmount = 180;
		break;
	case 1:
		SoundManager::GetInstance().Play(L"realod");
		weapons[2]->bulletAmount += 5;
		if (weapons[2]->bulletAmount >= weapons[2]->bulletMaxAmount)
			weapons[2]->bulletAmount = weapons[2]->bulletMaxAmount;
		break;
	case 2:
		SoundManager::GetInstance().Play(L"realod");
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
		else
			nowScene->msgBox->SpawnMsgBox2(L"obtainSkill");
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
			SoundManager::GetInstance().Play(L"airVoi");
			nowScene->obm.AddObject(new Airsupport(pos.x));

			skill2CoolTime = 5.0f;
			skill2Msg = false;
		}
		else
			nowScene->msgBox->SpawnMsgBox2(L"obtainSkill");

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
	if (target)
	{
		Camera::GetInstance().destCameraPos.x = target->pos.x;
	}
	else
	{
		if (pos.x > 960)
			Camera::GetInstance().destCameraPos.x = 959;
		else if(pos.x < -960)
			Camera::GetInstance().destCameraPos.x = -959;
		else if(pos.x > -960 && pos.x < 960)
			Camera::GetInstance().destCameraPos.x = pos.x;
	}

	Camera::GetInstance().destCameraPos.y = pos.y + 200;
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

		if (target)
			weapons[2]->Shoot();
	}

	if (Input::GetInstance().KeyDown('R'))
	{
		SetTarget(EnemyType::FlyingEnemy);

		if (target)
			weapons[3]->Shoot();
	}

	for (auto& weapon : weapons)
		weapon->Update(deltaTime);
}
