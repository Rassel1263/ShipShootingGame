#include "Header.h"
#include "RankingScene.h"
#include "Ranking.h"

void RankingScene::Init()
{
	Camera::GetInstance().destCameraPos = { 0, 0 };
	Camera::GetInstance().cameraPos = { 0, 0 };

	nowScene->obm.AddObject(new Ranking());
}

void RankingScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void RankingScene::Render()
{
	obm.Render();
}
