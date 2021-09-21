#pragma once
class Scene
{
public:
	ObjectManager obm;

	int curStage = 0;
	Scene* nextScene = NULL;

	Player* player = NULL;
	MiniMap* miniMap = NULL;
	MsgBox* msgBox = NULL;
	EnemyManager enemyManager;
	std::random_device rd;

	float gameTime = 180.0f;

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

