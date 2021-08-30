#pragma once

#include "Player.h"
#include "EnemyManager.h"

class Scene
{
public:
	ObjectManager obm;
	Player* player = NULL;
	EnemyManager enemyManager;
	std::random_device rd;
	
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	int GetRandomNumber(int min, int max);
};

