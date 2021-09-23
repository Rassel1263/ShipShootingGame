#pragma once
class BigPlane : public FlyingEnemy
{
public:

	bool intro = true;

	float restTime = 0.0f;
	float restTimer = 0.0f;

	float attackSpeed = 0.0f;
	float shootInterval = 0.0f;

	float outroTime = 0.0f;
	float effectTime = 0.0f;
	float effectTimer = 0.0f;


	int effectAmount = 0;

	int pattern = 0;


public:
	BigPlane(D3DXVECTOR2 pos);

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void Destroy() override;
	virtual bool Move(float deltaTime) override;
	virtual void Hit(float damage) override;
	void ChoosePattern();
	void UpdatePattern(float deltaTime);

	bool Intro(float deltaTime);
	bool Outro(float deltaTime);
	bool Pattern1(float deltaTime);
	bool Pattern2(float deltaTime);
	bool Pattern3(float deltaTime);
};

