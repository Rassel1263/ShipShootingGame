#include "Header.h"
#include "GameScene.h"
#include "Player.h"
#include "Ocean.h"

void GameScene::Init()
{
	obm.AddObject(player = new Player());
	obm.AddObject(new Ocean());

	enemyManager.SpawnEnemy(D3DXVECTOR2(0, 200), EnemyType::FloatingEnemy);
	enemyManager.SpawnEnemy(D3DXVECTOR2(200, 200), EnemyType::FlyingEnemy);
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}
