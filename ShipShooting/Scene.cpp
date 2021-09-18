#include "Header.h"
#include "Scene.h"

float Scene::score = 0.0f;

void Scene::Init()
{
}

void Scene::Update(float deltaTime)
{
	if (destScore > 0.0f)
	{
		float tempScore = destScore;
		destScore -= 1000 * deltaTime;
		score += tempScore - destScore;
	}

	if (curStage > 0)
	{
		if (Input::GetInstance().KeyDown(VK_F1))
			player->god = !player->god;

		if (Input::GetInstance().KeyDown(VK_F3))
			stopTime = !stopTime;
	}

	


	if (Input::GetInstance().KeyDown(VK_CONTROL))
		Time::GetInstance().timeScale = 30.0f;

	if (Input::GetInstance().KeyUp(VK_CONTROL))
		Time::GetInstance().timeScale = 1.0f;


	minute = gameTime / 60;
	second = (int)gameTime % 60;
	miniSecond = (gameTime - (int)gameTime) * 100;

	if (Input::GetInstance().KeyDown(VK_F4))
		Game::GetInstance().ChangeScene(new MainScene());

	if (Input::GetInstance().KeyDown(VK_F5))
		Game::GetInstance().ChangeScene(new GameScene());

	if (Input::GetInstance().KeyDown(VK_F6))
		Game::GetInstance().ChangeScene(new GameScene2());

	if (Input::GetInstance().KeyDown(VK_F7))
		Game::GetInstance().ChangeScene(new RankingScene());

	obm.Collision();
	obm.Update(deltaTime);
}

void Scene::Render()
{
	obm.Render();
}

int Scene::GetRandomNumber(int min, int max)
{
	std::default_random_engine rnd(rd());
	std::uniform_int_distribution<int> dis(min, max);

	return dis(rnd);
}

void Scene::AddScore(int score)
{
	destScore += score;
}

void Scene::LoadFile()
{
	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/colorShader.fx", 1);

	SoundManager::GetInstance().Create(L"Assets/Sound/Game.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/Machine.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/Cannon.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/Homing.mp3", 1);
	SoundManager::GetInstance().Create(L"Assets/Sound/explosion.mp3", 1);
	SoundManager::GetInstance().Play(L"Assets/Sound/Game.mp3", true);
}
