#pragma once
class GameScene2 : public Scene
{
public:
	float trashSpawnTime = 0.0f;

	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
};

