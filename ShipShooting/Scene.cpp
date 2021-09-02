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
		destScore -= 500 * deltaTime;
		score += tempScore - destScore;
	}

	if (curStage > 0)
	{
		if (Input::GetInstance().KeyDown(VK_F1))
			player->god = !player->god;

		if (Input::GetInstance().KeyDown(VK_F3))
			stopTime = !stopTime;
	}


	minute = gameTime / 60;
	second = (int)gameTime % 60;
	miniSecond = (gameTime - (int)gameTime) * 100;

	if (Input::GetInstance().KeyDown(VK_F4))
		Game::GetInstance().ChangeScene(new MainScene());

	if (Input::GetInstance().KeyDown(VK_F5))
		Game::GetInstance().ChangeScene(new GameScene());

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
