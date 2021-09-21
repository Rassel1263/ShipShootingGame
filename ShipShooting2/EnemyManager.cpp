#include "DXUT.h"
#include "EnemyManager.h"

void EnemyManager::SetSpawnTime(float floatSpawnTime, float flySpawnTime)
{
	this->floatSpawnTime = floatSpawnTime;
	this->flySpawnTime = flySpawnTime;
}

void EnemyManager::SetSpawnPos(EnemyType type)
{
	int spawnIndex = nowScene->GetRandomNumber(0, 2);

	D3DXVECTOR2 spawnPos = { 0, 0 };
	if (spawnIndex == 0) // аб
		spawnPos = D3DXVECTOR2(-1500, nowScene->GetRandomNumber(-100, 400));
	else if (spawnIndex == 1) // ╩С
		spawnPos = D3DXVECTOR2(nowScene->GetRandomNumber(-1200, 1200), 600);
	else if (spawnIndex == 2) // ©Л
		spawnPos = D3DXVECTOR2(1500, nowScene->GetRandomNumber(-100, 400));

	auto lambda = [=] {	SpawnEnemy(Camera::GetInstance().cameraPos + spawnPos, type); };

	if (spawnIndex == 0)
		spawnPos.x = -800;
	else if (spawnIndex == 1)
		spawnPos.y = 400;
	else if (spawnIndex == 2)
		spawnPos.x = 800;

	nowScene->obm.AddObject(new Effect(L"arrow.png", spawnPos, D3DXVECTOR2(1, 1), D3DXVECTOR2(0.5, 0.5), 2, false, 1.0f,
		spawnIndex * 90, lambda));
}

void EnemyManager::Spawner(float deltaTime)
{
	floatSpawnTimer += deltaTime;
	flySpawnTimer += deltaTime;

	if (floatSpawnTimer >= floatSpawnTime)
	{
		SetSpawnPos(EnemyType::FloatingEnemy);

		floatSpawnTimer = 0.0f;
	}

	if (flySpawnTimer >= flySpawnTime)
	{
		SetSpawnPos(EnemyType::FloatingEnemy);

		flySpawnTimer = 0.0f;
	}
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
	else if (enemyType == EnemyType::FlyingEnemy)
	{
		FlyingEnemy* flyingEnemy;
		nowScene->obm.AddObject(flyingEnemy = new FlyingEnemy(pos));
		flyingEnemys.push_back(flyingEnemy);
		enemy = flyingEnemy;
	}

	nowScene->miniMap->AddMiniObj(MINITAG::ENEMY, &enemy->pos, enemy);
	allEnemys.push_back(enemy);
}

void EnemyManager::SortEnemy(CEnemy* enemy, EnemyType enemyType)
{
	nowScene->miniMap->SortObj(enemy);

	auto ef = std::find(allEnemys.begin(), allEnemys.end(), enemy);

	if (ef != allEnemys.end())
		allEnemys.erase(ef);

	if (enemyType == EnemyType::FloatingEnemy)
	{
		auto ef = std::find(floatingEnemys.begin(), floatingEnemys.end(), enemy);

		if (ef != floatingEnemys.end())
			floatingEnemys.erase(ef);
	}
	else if (enemyType == EnemyType::FlyingEnemy)
	{
		auto ef = std::find(flyingEnemys.begin(), flyingEnemys.end(), enemy);

		if (ef != flyingEnemys.end())
			flyingEnemys.erase(ef);
	}
}
