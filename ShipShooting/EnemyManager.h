#pragma once
#include "CEnemy.h"
#include "FloatingEnemy.h"
#include "FlyingEnemy.h"

enum class EnemyType
{
	None,
	FloatingEnemy,
	FlyingEnemy,
};

class EnemyManager 
{
public:
	std::vector<CEnemy*> allEnemys;
	std::vector<FloatingEnemy*> floatingEnemys;
	std::vector<FlyingEnemy*> flyingEnemys;

	void SpawnEnemy(D3DXVECTOR2 pos, EnemyType enemyType);
};

