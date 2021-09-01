#include "Header.h"
#include "BigShip.h"

BigShip::BigShip(D3DXVECTOR2 pos) : FloatingEnemy(pos)
{
	type = EnemyType::FloatingEnemy;

	spr.LoadAll(L"Assets/Sprites/Unit/Boss/boss1.png");

	SetCollider(-900, -100, 900, 100, L"enemy");
	SetAbility(1000, 0);

	restTime = 1.0f;
}

void BigShip::Update(float deltaTime)
{
	UpdatePattern(deltaTime);

	CEnemy::Update(deltaTime);
}

void BigShip::Render()
{
	CEnemy::Render();
}

void BigShip::ChoosePattern()
{
	pattern = nowScene->GetRandomNumber(1, 3);


	if(pattern == 1)
	{
		attackTime = 3.0f;
		attackSpeed = 0.5f;
	}
	else if (pattern == 2)
	{
		attackTime = 5.0f;
		attackSpeed = 0.3f;
	}
	else if (pattern == 3)
	{
		attackTime = 7.0f;
		attackSpeed = 0.3f;
	}
}

void BigShip::UpdatePattern(float deltaTime)
{
	bool endPattern = false;

	attackTimer += deltaTime;

	if (pattern == 1)
		endPattern = Pattern1(deltaTime);
	else if (pattern == 2)
		endPattern = Pattern2(deltaTime);
	else if (pattern == 3)
		endPattern = Pattern3(deltaTime);

	if (!endPattern)
	{
		restTimer += deltaTime;

		if (restTimer >= restTime)
		{
			restTimer = 0.0f;
			attackTimer = 0.0f;

			ChoosePattern();
		}
	}
}

bool BigShip::Pattern1(float deltaTime)
{
	if (attackTimer >= attackTime)
		return false;

	return true;
}

bool BigShip::Pattern2(float deltaTime)
{
	if (attackTimer >= attackTime)
		return false;

	return true;
}

bool BigShip::Pattern3(float deltatime)
{
	if (attackTimer >= attackTime)
		return false;

	return true;
}
