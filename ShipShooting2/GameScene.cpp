#include "DXUT.h"
#include "GameScene.h"

void GameScene::Init()
{
	Scene::LoadAll();
	curStage = 1;
	nextScene = new GameScene2();

	SoundManager::GetInstance().Play(L"stage1", true);

	obm.AddObject(new Map());
	obm.AddObject(miniMap = new MiniMap());
	obm.AddObject(player = new Player());
	obm.AddObject(msgBox = new MsgBox());
	obm.AddObject(new StageFont(StageFont::Type::START));

	obstacleManager.Init(300, 1000);

	enemyManager.SetSpawnTime(4.0f, 7.0f);

	nowScene->obm.AddObject(new Font(L"kk", minute, D3DXVECTOR2(-100, 465), D3DXVECTOR2(1, 1), 30.0f, 1, 0));
	nowScene->obm.AddObject(new Font(L"kk", second, D3DXVECTOR2(0, 465), D3DXVECTOR2(1, 1), 30.0f, 1, 0));
	nowScene->obm.AddObject(new Font(L"kk", miniSecond, D3DXVECTOR2(100, 465), D3DXVECTOR2(1, 1), 30.0f, 1, 0));
	nowScene->obm.AddObject(new Font(L"kk", score, D3DXVECTOR2(850, 465), D3DXVECTOR2(1, 1), 30.0f, 3, 0));
}

void GameScene::Update(float deltaTime)
{
	if(!stopTime)
		gameTime -= deltaTime;

	minute = gameTime / 60.0f;
	second = (int)gameTime % 60;
	miniSecond = (gameTime - (int)gameTime) * 100;

	if (player->moveDistance >= destination && !spawnBoss)
	{
		nowScene->enemyManager.SpawnEnemy(D3DXVECTOR2(nowScene->player->pos.x, nowScene->player->pos.y + 500), EnemyType::BigShip);
		player->moveDistance = destination;
	}

	if (gameTime <= 0.0 && !timeOver)
	{
		timeOver = true;
		nowScene->obm.AddObject(new StageFont(StageFont::Type::FAIL));
	}

	if (nowScene->stageStart && !nowScene->spawnBoss)
	{
		obstacleManager.Update(deltaTime);
		enemyManager.Spawner(deltaTime);
	}

	if (destScore > 0.0f)
	{
		float tempScore = destScore;
		destScore -= 1000 * deltaTime;
		score += tempScore - destScore;
	}

	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}

void GameScene::UIRender()
{
	Scene::UIRender();
}
