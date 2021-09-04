#include "Header.h"
#include "EnemyManager.h"
#include "Effect.h"
#include "BigShip.h"
#include "BigPlane.h"

void EnemyManager::Init(float floatSpawnTime, float airSpawnTime)
{
	this->floatSpawnTime = floatSpawnTime;
	this->airSpawnTime = airSpawnTime;

	this->floatSpawnTimer = floatSpawnTime;
	this->airSpawnTimer = airSpawnTime;
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

	if (enemyType == EnemyType::BigShip)
	{
		FlyingEnemy *flyingEnemy;
		nowScene->obm.AddObject(flyingEnemy = new BigPlane(pos));
		flyingEnemys.push_back(flyingEnemy);
		boss = flyingEnemy;
		enemy = flyingEnemy;
	}


	allEnemys.push_back(enemy);
}


void EnemyManager::SortEnemyGroups(CEnemy* enemy, EnemyType enemyType)
{
	auto it = std::find(allEnemys.begin(), allEnemys.end(), enemy);

	if(it != allEnemys.end())
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
}
