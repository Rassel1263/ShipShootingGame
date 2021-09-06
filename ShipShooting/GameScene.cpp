#include "Header.h"
#include "GameScene.h"
#include "Player.h"
#include "Ocean.h"
#include "Mine.h"
#include "Trash.h"
#include "BigShip.h"
#include "PlayerUI.h"
#include "Font.h"
#include "Item.h"
#include "YouDie.h"

void GameScene::Init()
{
	curStage = 1;
	nextScene = new GameScene2();

	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/colorShader.fx", 1);

	obm.AddObject(player = new Player());
	obm.AddObject(new PlayerUI(player));
	obm.AddObject(new Ocean());
	enemyManager.Init(4.0f, 6.0f, 10.0f);

	obm.AddObject(new Font(L"Number/", minute, D3DXVECTOR2(-120, 450), D3DXVECTOR2(2, 2), 60, 0));
	obm.AddObject(new Font(L"Number/", second, D3DXVECTOR2(40, 435), D3DXVECTOR2(1, 1), 30, 1));
	obm.AddObject(new Font(L"Number/", miniSecond, D3DXVECTOR2(120, 435), D3DXVECTOR2(1, 1), 30, 2));

	obm.AddObject(new Font(L"Number/", score, D3DXVECTOR2(-600, 450), D3DXVECTOR2(2, 2), 60, 3));

	MiniMap::GetInstance().Init();

	maxProgress = 27000;
}

void GameScene::Update(float deltaTime)
{
	if (!stopTime)
		gameTime -= deltaTime;

	if (Input::GetInstance().KeyDown('F'))
	{
		for (int i = 0; i < 2; ++i)
		{
			for(int j = -i; j <= i; j += 2)
				enemyManager.SpawnSubEnemy(D3DXVECTOR2(j * 150, 500 + i * 100), 300, 0, 180, 300);
		}
	}

	if (gameTime <= 0.0f)
		obm.AddObject(new YouDie());

	if (progress >= maxProgress && !spawnBoss)
	{
		progress = maxProgress;
		spawnBoss = true;
		enemyManager.SpawnEnemy(D3DXVECTOR2(0, 500), EnemyType::BigShip);
	}

	if (progress < maxProgress)
		progress += player->ability.speed * deltaTime;

	trashSpawnTime += deltaTime;
	if (trashSpawnTime >= 3.0f)
	{
		trashSpawnTime = 0.0f;
		nowScene->obm.AddObject(new Trash(D3DXVECTOR2(GetRandomNumber(-960, 960), 700)));
	}

	MiniMap::GetInstance().Update(deltaTime);

	if(!spawnBoss)
		enemyManager.SpawnManager(deltaTime);



	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();

	if (Time::GetInstance().timeScale != 0.0f)
		MiniMap::GetInstance().Render();
}
