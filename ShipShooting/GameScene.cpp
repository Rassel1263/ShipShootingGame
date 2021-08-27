#include "Header.h"
#include "GameScene.h"
#include "Unit.h"

void GameScene::Init()
{
	obm.AddObject(new Unit());
}

void GameScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}
