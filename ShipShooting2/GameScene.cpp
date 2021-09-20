#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	Scene::LoadAll();

	obm.AddObject(new Map());
	obm.AddObject(miniMap = new MiniMap());
	obm.AddObject(new Player());

	enemyManager.SpawnEnemy(D3DXVECTOR2(200, 400), EnemyType::FloatingEnemy);
	enemyManager.SpawnEnemy(D3DXVECTOR2(-200, 400), EnemyType::FlyingEnemy);
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}

void GameScene::UIRender()
{
	Scene::UIRender();
}
