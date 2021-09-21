#include "DXUT.h"
#include "ObstacleManager.h"

void ObstacleManager::Init(float gMax, float rMax)
{
	this->gMaxDistance = gMax;
	this->rMaxDistance = rMax;
}

void ObstacleManager::Update(float deltaTime)
{
	gDistance += nowScene->player->dps;
	rDistnace += nowScene->player->dps;

	if (gDistance > gMaxDistance)
	{
		nowScene->obm.AddObject(new Obstacle(D3DXVECTOR2(nowScene->GetRandomNumber(-1500, 1500), nowScene->player->pos.y + 900), Obstacle::ObstalceType::GARBAGE));
		gDistance = 0.0f;
	}

	if (rDistnace > rMaxDistance)
	{
		nowScene->obm.AddObject(new Obstacle(D3DXVECTOR2(nowScene->GetRandomNumber(-1500, 1500), nowScene->player->pos.y + 900), Obstacle::ObstalceType::ROCK));
		rDistnace = 0.0f;
	}
}
