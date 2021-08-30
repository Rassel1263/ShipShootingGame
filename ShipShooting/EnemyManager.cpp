#include "Header.h"
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

	if (enemyType == EnemyType::FlyingEnemy)
	{
		FlyingEnemy* flyingEnemy;
		nowScene->obm.AddObject(flyingEnemy = new FlyingEnemy(pos));
		flyingEnemys.push_back(flyingEnemy);
		enemy = flyingEnemy;
	}

	allEnemys.push_back(enemy);
}
