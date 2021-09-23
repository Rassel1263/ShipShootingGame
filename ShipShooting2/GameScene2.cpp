#include "DXUT.h"
#include "GameScene2.h"

void GameScene2::Init()
{
	Scene::LoadAll();
	curStage = 2;
	nextScene = new RankingScene();

	SoundManager::GetInstance().Play(L"stage1", true);

	obm.AddObject(new Map());
	obm.AddObject(miniMap = new MiniMap());
	obm.AddObject(player = new Player());
	obm.AddObject(msgBox = new MsgBox());
	obm.AddObject(new StageFont(StageFont::Type::START));

	obstacleManager.Init(200, 700);

	enemyManager.SetSpawnTime(2.5f, 5.0f);

	nowScene->obm.AddObject(new Font(L"kk", minute, D3DXVECTOR2(-100, 465), D3DXVECTOR2(1, 1), 30.0f, 1, 0));
	nowScene->obm.AddObject(new Font(L"kk", second, D3DXVECTOR2(0, 465), D3DXVECTOR2(1, 1), 30.0f, 1, 0));
	nowScene->obm.AddObject(new Font(L"kk", miniSecond, D3DXVECTOR2(100, 465), D3DXVECTOR2(1, 1), 30.0f, 1, 0));
}

void GameScene2::Update(float deltaTime)
{
	if (!stopTime)
		gameTime -= deltaTime;

	minute = gameTime / 60.0f;
	second = (int)gameTime % 60;
	miniSecond = (gameTime - (int)gameTime) * 100;

	if (player->moveDistance >= destination && !spawnBoss)
	{
		nowScene->enemyManager.SpawnEnemy(D3DXVECTOR2(nowScene->player->pos.x, nowScene->player->pos.y + 500), EnemyType::BigPlane);
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

void GameScene2::Render()
{
	Scene::Render();
}

void GameScene2::UIRender()
{
	Scene::UIRender();
}
