#pragma once

#include "Player.h"
#include "EnemyManager.h"

class Scene
{
public:
	static float score;
	float destScore = 0.0f;
	float gameTime = 180.0f;

	float minute = 0.0f;
	float second = 0.0f;
	float miniSecond = 0.0f;

	bool stopTime = false;
	bool spawnBoss = false;

	int curStage = 0;
	Scene* nextScene = NULL;

	ObjectManager obm;
	Player* player = NULL;
	EnemyManager enemyManager;
	std::random_device rd;

	
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void AddScore(int score);
	int GetRandomNumber(int min, int max);
};

