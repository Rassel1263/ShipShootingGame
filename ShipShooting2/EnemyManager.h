#pragma once
class EnemyManager 
{
public:
	std::vector<CEnemy*> allEnemys;
	std::vector<FloatingEnemy*> floatingEnemys;
	std::vector<FlyingEnemy*> flyingEnemys;

public:
	void SpawnEnemy(D3DXVECTOR2 pos, EnemyType enemyType);
	void SortEnemy(CEnemy* enemy, EnemyType enemyType);
};

