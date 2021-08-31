#include "Header.h"
#include "GameScene.h"
#include "Player.h"
#include "Ocean.h"
#include "Mine.h"

void GameScene::Init()
{
	obm.AddObject(player = new Player());
	obm.AddObject(new Ocean());
	obm.AddObject(new Mine(D3DXVECTOR2(0, -100)));

	enemyManager.Init(3.0f);

	//enemyManager.SpawnEnemy(D3DXVECTOR2(0, 200), EnemyType::FloatingEnemy);
	//enemyManager.SpawnEnemy(D3DXVECTOR2(200, 200), EnemyType::FlyingEnemy);
}

void GameScene::Update(float deltaTime)
{
	enemyManager.FloatSpawnManager(deltaTime);

	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}
