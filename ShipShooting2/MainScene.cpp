#include "DXUT.h"
#include "MainScene.h"

void MainScene::Init()
{
	curStage = 0;
	score = 0.0f;

	Scene::LoadAll();

	SoundManager::GetInstance().Play(L"main", true);

	if (TextureManager::GetInstance().GetThreadCount() <= 0)
		nowScene->obm.AddObject(new LoadSprite());
	else
		nowScene->obm.AddObject(new Main());

}

void MainScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void MainScene::Render()
{
	Scene::Render();
}
