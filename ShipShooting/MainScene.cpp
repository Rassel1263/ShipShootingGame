#include "Header.h"
#include "MainScene.h"
#include "Main.h"

void MainScene::Init()
{
	score = 0.0f;

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
