#pragma once

class BigShip : public FloatingEnemy
{
public:
	float restTime = 0.0f;
	float restTimer = 0.0f;

	float attackSpeed = 0.0f;
	float bulletInterval = 0.0f;

	int pattern = 0;

public:
	BigShip(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void ChoosePattern();
	void UpdatePattern(float deltaTime);
	bool Pattern1(float deltaTime);
	bool Pattern2(float deltaTime);
	bool Pattern3(float deltatime);
};

