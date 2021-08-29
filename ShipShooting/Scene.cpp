#include "Header.h"
#include "Scene.h"

void Scene::Init()
{
}

void Scene::Update(float deltaTime)
{
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
