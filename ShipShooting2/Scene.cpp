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
