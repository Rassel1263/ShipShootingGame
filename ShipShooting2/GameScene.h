#pragma once
class GameScene : public Scene
{
public:
	float minute = 0.0f;
	float second = 0.0f;
	float miniSecond = 0.0f;
	bool timeOver = false;

	ObstacleManager obstacleManager;

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void UIRender() override;
};

