#pragma once
class Scene
{
public:
	ObjectManager obm;
	MiniMap* miniMap = NULL;
	EnemyManager enemyManager;
	std::random_device rd;

	bool spawnBoss = false;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void UIRender();

	void LoadAll();

	int GetRandomNumber(int min, int max);
	float GetAngleFromTarget(D3DXVECTOR2 pos, D3DXVECTOR2 targetPos);

	D3DXVECTOR2 GetRandomVector(int minX, int maxX, int minY, int maxY);

};

