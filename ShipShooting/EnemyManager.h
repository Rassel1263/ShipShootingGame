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

	CEnemy* boss = NULL;

public:
	float floatSpawnTimer = 0.0f;
	float floatSpawnTime = 3.0f;

	float airSpawnTimer = 0.0f;
	float airSpawnTime = 5.0f;

	float subSpawnTimer = 0.0f;
	float subSpawnTime = 3.0f;

	float spawnInterval = 0.0f;
	int amount = 0;
	bool leftSpawn = false;
	bool subSpawn = false;
	subFormation form;

	void Init(float floatSpawnTime, float airSpawnTime, float subSpawnTime);
	void SpawnEnemy(D3DXVECTOR2 pos, EnemyType enemyType);
	void SpawnSubEnemy(D3DXVECTOR2 pos, float startAngle, float addAngle, float maxAngle, float speed);
	void SpawnManager(float deltaTime);
	void SortEnemyGroups(CEnemy* enemy, EnemyType enemyType);
};

