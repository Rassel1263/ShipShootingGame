#pragma once
class EnemyManager 
{
public:
	std::vector<CEnemy*> allEnemys;
	std::vector<FloatingEnemy*> floatingEnemys;
	std::vector<FlyingEnemy*> flyingEnemys;

	float floatSpawnTime = 0.0f;
	float floatSpawnTimer = 0.0f;

	float flySpawnTime = 0.0f;
	float flySpawnTimer = 0.0f;

public:
	void SetSpawnTime(float floatSpawnTime, float flySpawnTime);

	void SetSpawnPos(EnemyType type);
	void Spawner(float deltaTime);

	void SpawnEnemy(D3DXVECTOR2 pos, EnemyType enemyType);
	void SortEnemy(CEnemy* enemy, EnemyType enemyType);
};

