#include "Header.h"
#include "EnemyManager.h"
#include "Effect.h"
#include "BigShip.h"
#include "BigPlane.h"
#include "SubFlyingEnemy.h"

void EnemyManager::Init(float floatSpawnTime, float airSpawnTime, float subSpawnTime)
{
	this->floatSpawnTime = floatSpawnTime;
	this->airSpawnTime = airSpawnTime;

	this->floatSpawnTimer = floatSpawnTime;
	this->airSpawnTimer = airSpawnTime;

	this->subSpawnTime = subSpawnTime;
}

void EnemyManager::SpawnEnemy(D3DXVECTOR2 pos, EnemyType enemyType)
{
	CEnemy* enemy = NULL;

	if (enemyType == EnemyType::FloatingEnemy)
	{
		FloatingEnemy* floatingEnemy;
		nowScene->obm.AddObject(floatingEnemy = new FloatingEnemy(pos));
		floatingEnemys.push_back(floatingEnemy);
		enemy = floatingEnemy;
	}

	if (enemyType == EnemyType::FlyingEnemy)
	{
		FlyingEnemy* flyingEnemy;
		nowScene->obm.AddObject(flyingEnemy = new FlyingEnemy(pos));
		flyingEnemys.push_back(flyingEnemy);
		enemy = flyingEnemy;
	}

	if (enemyType == EnemyType::BigShip)
	{
		FloatingEnemy* floatingEnemy;
		nowScene->obm.AddObject(floatingEnemy = new BigShip(pos));
		floatingEnemys.push_back(floatingEnemy);
		boss = floatingEnemy;
		enemy = floatingEnemy;
	}

	if (enemyType == EnemyType::BigPlane)
	{
		FlyingEnemy* flyingEnemy;
		nowScene->obm.AddObject(flyingEnemy = new BigPlane(pos));
		flyingEnemys.push_back(flyingEnemy);
		boss = flyingEnemy;
		enemy = flyingEnemy;
	}


	allEnemys.push_back(enemy);
}

void EnemyManager::SpawnSubEnemy(D3DXVECTOR2 pos, float startAngle, float addAngle, float maxAngle, float speed)
{
	FlyingEnemy* flyingEnemy;
	nowScene->obm.AddObject(flyingEnemy = new SubFlyingEnemy(pos, startAngle, addAngle, maxAngle, speed));
	flyingEnemys.push_back(flyingEnemy);
	allEnemys.push_back(flyingEnemy);
}


void EnemyManager::SortEnemyGroups(CEnemy* enemy, EnemyType enemyType)
{
	auto it = std::find(allEnemys.begin(), allEnemys.end(), enemy);

	if (it != allEnemys.end())
		allEnemys.erase(it);

	if (enemyType == EnemyType::FloatingEnemy)
	{
		auto it = std::find(floatingEnemys.begin(), floatingEnemys.end(), enemy);

		if (it != floatingEnemys.end())
			floatingEnemys.erase(it);
	}

	if (enemyType == EnemyType::FlyingEnemy)
	{
		auto it = std::find(flyingEnemys.begin(), flyingEnemys.end(), enemy);

		if (it != flyingEnemys.end())
			flyingEnemys.erase(it);
	}
}

void EnemyManager::SpawnManager(float deltaTime)
{
	floatSpawnTimer += deltaTime;
	airSpawnTimer += deltaTime;
	subSpawnTimer += deltaTime;

	if (floatSpawnTimer >= floatSpawnTime)
	{
		floatSpawnTimer = 0.0f;

		D3DXVECTOR2 randPos = D3DXVECTOR2(nowScene->GetRandomNumber(-300, 300), 450);

		auto lambda = [=] {SpawnEnemy(randPos + D3DXVECTOR2(0, 300), EnemyType::FloatingEnemy); };


		nowScene->obm.AddObject(new Effect(L"enemyPos.png", randPos, D3DXVECTOR2(1, 1), 0, 1.0f, true, 0, lambda));
	}

	if (airSpawnTimer >= airSpawnTime)
	{
		airSpawnTimer = 0.0f;

		D3DXVECTOR2 randPos = D3DXVECTOR2(nowScene->GetRandomNumber(-300, 300), 450);

		auto lambda = [=] {SpawnEnemy(randPos + D3DXVECTOR2(0, 300), EnemyType::FlyingEnemy); };


		nowScene->obm.AddObject(new Effect(L"enemyPos.png", randPos, D3DXVECTOR2(1, 1), 0, 1.0f, true, 0, lambda));
	}

	if (subSpawnTimer >= subSpawnTime)
	{
		amount = nowScene->GetRandomNumber(2, 3);
		form = (subFormation)nowScene->GetRandomNumber(0, 1);
		leftSpawn = nowScene->GetRandomNumber(0, 1);
		subSpawn = true;
		subSpawnTimer = 0.0f;
	}

	if (subSpawn)
	{
		if (form == subFormation::V)
		{
			subSpawnTimer = 0.0f;
			D3DXVECTOR2 randPos = D3DXVECTOR2(nowScene->GetRandomNumber(-300, 300), 450);

			for (int i = 0; i < amount; ++i)
			{
				for (int j = -i; j <= i; j += 2)
					SpawnSubEnemy(D3DXVECTOR2(randPos.x + j * 150, randPos.y + i * 100), -90, 0, 0, 300);
			}

			subSpawn = false;
		}
		else if(form == subFormation::Circle)
		{
			spawnInterval += deltaTime;

			if (spawnInterval >= 0.5f)
			{
				if(leftSpawn)
					SpawnSubEnemy(D3DXVECTOR2(-700, 550), -90, 30, 0, 300);
				else
					SpawnSubEnemy(D3DXVECTOR2(700, 550), -90, -30, 0, 300);

				spawnInterval = 0.0f;
				amount--;
			}

			if (amount <= 0)
				subSpawn = false;
		}
	}

}
