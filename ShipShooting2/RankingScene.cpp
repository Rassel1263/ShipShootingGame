#include "DXUT.h"
#include "RankingScene.h"
#include "WriteRank.h"

void RankingScene::Init()
{
	Camera::GetInstance().cameraPos = { 0, 0 };
	Camera::GetInstance().destCameraPos = { 0,0 };

	obm.AddObject(new WriteRank());
}

void RankingScene::Update(float deltaTime)
{
	Scene::Update(deltaTime);
}

void RankingScene::Render()
{
	Scene::Render();
}

void RankingScene::UIRender()
{
	Scene::UIRender();
}
