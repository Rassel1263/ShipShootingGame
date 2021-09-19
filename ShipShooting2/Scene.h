#pragma once
class Scene
{
public:
	ObjectManager obm;
	bool spawnBoss = false;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void UIRender();
};

