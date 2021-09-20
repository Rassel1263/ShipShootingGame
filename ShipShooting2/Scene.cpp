#include "DXUT.h"
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

void Scene::UIRender()
{
	obm.UIRender();
}

void Scene::LoadAll()
{
	ShaderManager::GetInstance().CreateEffect("Color", L"Assets/Shader/ColorShader.fx", 1);
}

int Scene::GetRandomNumber(int min, int max)
{
	std::default_random_engine rnd(rd());
	std::uniform_int_distribution<int> dis(min, max);

	return dis(rnd);
}

float Scene::GetAngleFromTarget(D3DXVECTOR2 pos, D3DXVECTOR2 targetPos)
{
	D3DXVECTOR2 distance = targetPos - pos;
	return D3DXToDegree(atan2(distance.y, distance.x));
}

D3DXVECTOR2 Scene::GetRandomVector(int minX, int maxX, int minY, int maxY)
{
	std::default_random_engine rnd(rd());
	std::uniform_int_distribution<int> x(minX, maxX);
	std::uniform_int_distribution<int> y(minY, maxY);

	return D3DXVECTOR2((float)x(rnd), (float)y(rnd));
}
