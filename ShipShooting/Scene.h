#pragma once

#include "CEnemy.h"
#include "Player.h"

class Scene
{
public:
	ObjectManager obm;
	Player* player = NULL;
	CEnemy* enemy = NULL;
	std::random_device rd;
	
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	int GetRandomNumber(int min, int max);
};

