#include "Header.h"
#include "MainScene.h"
#include "Main.h"

void MainScene::Init()
{
	obm.AddObject(new Main());
}

void MainScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void MainScene::Render()
{
	Scene::Render();
}
