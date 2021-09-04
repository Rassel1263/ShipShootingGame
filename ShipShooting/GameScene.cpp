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
	obm.AddObject(new Mine(D3DXVECTOR2(0, -100)));
	obm.AddObject(new Trash(D3DXVECTOR2(0, 200)));
	enemyManager.Init(5.0f, 7.0f);

	obm.AddObject(new Font(L"Number/", minute, D3DXVECTOR2(-120, 450), D3DXVECTOR2(2, 2), 60, 0));
	obm.AddObject(new Font(L"Number/", second, D3DXVECTOR2(40, 435), D3DXVECTOR2(1, 1), 30, 1));
	obm.AddObject(new Font(L"Number/", miniSecond, D3DXVECTOR2(120, 435), D3DXVECTOR2(1, 1), 30, 2));

	obm.AddObject(new Font(L"Number/", score, D3DXVECTOR2(-600, 450), D3DXVECTOR2(2, 2), 60, 3));

	MiniMap::GetInstance().Init();

	maxProgress = 27000;


	//enemyManager.SpawnEnemy(D3DXVECTOR2(0, 200), EnemyType::FloatingEnemy);
	//enemyManager.SpawnEnemy(D3DXVECTOR2(200, 200), EnemyType::FlyingEnemy);
}

void GameScene::Update(float deltaTime)
{
	if (Input::GetInstance().KeyDown('J'))
	{
		progress = maxProgress;
		spawnBoss = true;
		enemyManager.SpawnEnemy(D3DXVECTOR2(0, 500), EnemyType::BigShip);
	}

	if (Input::GetInstance().KeyDown('Y'))
		AddScore(1000);

	if (Input::GetInstance().KeyDown(VK_CONTROL))
		Time::GetInstance().timeScale = 10.0f;

	if(Input::GetInstance().KeyUp(VK_CONTROL))
		Time::GetInstance().timeScale = 1.0f;

	if (!stopTime)
		gameTime -= deltaTime;

	if (gameTime <= 0.0f)
		obm.AddObject(new YouDie());

	if (progress >= maxProgress && !spawnBoss)
	{
		progress = maxProgress;
		spawnBoss = true;
		enemyManager.SpawnEnemy(D3DXVECTOR2(0, 500), EnemyType::BigShip);
	}
	
	if(progress < maxProgress)
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

	if(Time::GetInstance().timeScale != 0.0f)
		MiniMap::GetInstance().Render();
}
