#include "Header.h"
#include "RankingScene.h"
#include "Ranking.h"

void RankingScene::Init()
{
	nowScene->obm.AddObject(new Ranking());
}

void RankingScene::Update(float deltaTime)
{
	obm.Update(deltaTime);
}

void RankingScene::Render()
{
	obm.Render();
}
