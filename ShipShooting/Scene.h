#pragma once

#include "CEnemy.h"
#include "Player.h"

class Scene
{
public:
	ObjectManager obm;
	Player* player = NULL;
	CEnemy* enemy = NULL;
	
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
};

