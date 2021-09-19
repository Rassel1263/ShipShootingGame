#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	obm.AddObject(new Map());
	obm.AddObject(new Player());
	obm.AddObject(new FloatingEnemy(D3DXVECTOR2(200, 200)));
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
