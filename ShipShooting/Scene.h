#pragma once

class Scene
{
public:
	ObjectManager obm;
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
};

