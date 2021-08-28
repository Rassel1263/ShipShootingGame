#include "Header.h"
#include "GameScene.h"
#include "Player.h"
#include "Ocean.h"

void GameScene::Init()
{
	obm.AddObject(player = new Player());
	obm.AddObject(enemy = new CEnemy());
	obm.AddObject(new Ocean());
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}
