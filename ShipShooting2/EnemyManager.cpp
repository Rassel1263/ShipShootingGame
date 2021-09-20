#include "DXUT.h"
#include "EnemyManager.h"

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

	allEnemys.push_back(enemy);
}

void EnemyManager::SortEnemy(CEnemy* enemy, EnemyType enemyType)
{
	auto ef = std::find(allEnemys.begin(), allEnemys.end(), enemy);

	if (ef != allEnemys.end())
		allEnemys.erase(ef);

	if (enemyType == EnemyType::FloatingEnemy)
	{
		auto ef = std::find(floatingEnemys.begin(), floatingEnemys.end(), enemy);

		if (ef != floatingEnemys.end())
			floatingEnemys.erase(ef);
	}
}
