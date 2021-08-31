#pragma once
#include "CEnemy.h"
#include "FloatingEnemy.h"
#include "FlyingEnemy.h"


class EnemyManager 
{
public:
	std::vector<CEnemy*> allEnemys;
	std::vector<FloatingEnemy*> floatingEnemys;
	std::vector<FlyingEnemy*> flyingEnemys;

public:
	float floatSpawnTimer = 0.0f;
	float floatSpawnTime = 3.0f;

	void Init(float spawnTime);
	void SpawnEnemy(D3DXVECTOR2 pos, EnemyType enemyType);
	void FloatSpawnManager(float deltaTime);
	void SortEnemyGroups(CEnemy* enemy, EnemyType enemyType);
};

