#include "Header.h"
#include "GameScene.h"
#include "Player.h"
#include "Ocean.h"
#include "Mine.h"
#include "BigShip.h"
#include "PlayerUI.h"
#include "Font.h"

void GameScene::Init()
{
	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/colorShader.fx", 1);

	obm.AddObject(player = new Player());
	obm.AddObject(new PlayerUI(player));
	obm.AddObject(new Ocean());
	obm.AddObject(new Mine(D3DXVECTOR2(0, -100)));
	enemyManager.Init(10.0f, 10.0f);
	enemyManager.SpawnEnemy(D3DXVECTOR2(0, 200), EnemyType::FlyingEnemy);

	obm.AddObject(new Font(D3DXVECTOR2(-30, 0), D3DXVECTOR2(1, 1), 30, gameTime));
	//enemyManager.SpawnEnemy(D3DXVECTOR2(0, 300), EnemyType::BigShip);

	//enemyManager.SpawnEnemy(D3DXVECTOR2(0, 200), EnemyType::FloatingEnemy);
	//enemyManager.SpawnEnemy(D3DXVECTOR2(200, 200), EnemyType::FlyingEnemy);
}

void GameScene::Update(float deltaTime)
{
	gameTime -= deltaTime;

	//enemyManager.FloatSpawnManager(deltaTime);

	Scene::Update(deltaTime);
}

void GameScene::Render()
{
	Scene::Render();
}
