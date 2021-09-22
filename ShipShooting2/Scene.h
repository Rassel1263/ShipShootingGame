#pragma once
class Scene
{
public:
	ObjectManager obm;

	static float score;
	float destScore = 0.0f;
	int destination = 18000;

	int curStage = 0;

	Scene* nextScene = NULL;

	Player* player = NULL;
	MiniMap* miniMap = NULL;
	MsgBox* msgBox = NULL;
	EnemyManager enemyManager;
	std::random_device rd;

	float gameTime = 180.0f;

	bool stopTime = true;
	bool stageStart = false;
	bool spawnBoss = false;

	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void UIRender();

	void LoadAll();
	void AddScore(int score);

	int GetRandomNumber(int min, int max);
	float GetAngleFromTarget(D3DXVECTOR2 pos, D3DXVECTOR2 targetPos);

	D3DXVECTOR2 GetRandomVector(int minX, int maxX, int minY, int maxY);
};

